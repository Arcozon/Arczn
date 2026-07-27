#include "arczn.h"
#include "petri.h"

static const int64_t	dirVec[NONE + 1][2] = {
		[UP]	= {0, -1},
		[LEFT]	= {-1, 0},
		[DOWN]	= {0, 1},
		[RIGHT]	= {1, 0},
		[NONE]	= {0, 0}
};

__always_inline static inline
bool	_hasNeighbour(uint8_t *arr[], const size_t width, const size_t height, const size_t x, const size_t _y) {
	const size_t y = 2 * _y;

	if (x != 0) {
		const size_t	tX = x - 1;
		if (arr[y][tX / 8] & MASK(tX % 8))
			return (true);
	}
	if (x + 1 < width) {
		if (arr[y][x / 8] & MASK(x % 8))
			return (true);
	}
	if (y != 0) {
		const size_t tY = y - 1;
		if (arr[tY][x / 8] & MASK(x % 8))
			return (true);
	}
	if (_y + 1 < height) {
		if (arr[y + 1][x / 8] & MASK(x % 8))
			return (true);
	}
	return (false);
}

__always_inline static inline
uint8_t	getPossibility(const t_tab *tab, const size_t x, const size_t y) {
	uint8_t	res = 0b0000;

	if (x != 0) { // Check left
		if (!_hasNeighbour(tab->arr, tab->width, tab->height, x - 1, y))
			res |= MASK(LEFT);
	}
	if (x + 1 < tab->width) { // Check right
		if (!_hasNeighbour(tab->arr, tab->width, tab->height, x + 1, y))
			res |= MASK(RIGHT);
	}
	if (y != 0) { // Check up
		if (!_hasNeighbour(tab->arr, tab->width, tab->height, x, y - 1))
			res |= MASK(UP);
	}
	if (y + 1 < tab->height) { // Check down
		if (!_hasNeighbour(tab->arr, tab->width, tab->height, x, y + 1))
			res |= MASK(DOWN);
	}
	return (res);
}



__always_inline static inline
void	_addPoint(t_cluster *restrict cluster, const t_point *restrict oldPoint, size_t direction) {
	static t_point	newPoint;
	
	newPoint = *oldPoint;
	newPoint.x += dirVec[direction][0];
	newPoint.y += dirVec[direction][1];
	newPoint.distance += 1;
	clusterAdd(cluster, &newPoint);
	// TODO: calc new Point weight
}

__always_inline
void	_joinPoint(t_cluster *cluster, t_point nPoint, const uint8_t choice, uint8_t *tab[]) {
	const size_t	bX = nPoint.x;
	const size_t	bY = nPoint.y * 2;

	nPoint.distance += 1;
	if (choice == UP) {
		tab[bY - 1][bX / 8] |= MASK(bX % 8);
		nPoint.y -= 1;
		clusterAdd(cluster, &nPoint);
	} else if (choice == DOWN) {
		tab[bY + 1][bX / 8] |= MASK(bX % 8);
		nPoint.y += 1;
		clusterAdd(cluster, &nPoint);
	} else if (choice == LEFT) {
		const size_t	nX = bX - 1;
		tab[bY][nX / 8] |= MASK(nX % 8);
		nPoint.x -= 1;
		clusterAdd(cluster, &nPoint);
	} else if (choice == RIGHT) {
		const size_t	nX = bX;
		tab[bY][nX / 8] |= MASK(nX % 8);
		nPoint.x += 1;
		clusterAdd(cluster, &nPoint);
	} else {
		printf("Error: "__FILE_NAME__":%d\n", __LINE__);
		abort();
	}
}

__always_inline static
void	_initCluster(const t_start *start, const size_t HashTableSize, t_vec *vClusters) {
	t_cluster		cluster = {.xOrigin = start->x /2, .yOrigin = start->y / 2,
			// .getClusterWeightFn = NULL,
			.getClusterWeightFn = GCW_Linear,
			.getPointWeightFn = GPW_distance,
			.chosePossibilityFn = CPF_random};
	
	cluster.ht = ht_create(HashTableSize, pointHash, pointDup, pointCmp, free);
	cluster.ratioWeight = start->weight;
	cluster.weight = start->weight;
	
	if (!cluster.ht || fTree_create(&cluster.weightPoints))
		abort();

	t_cluster	*pCluster = vec_add(vClusters, &cluster);
	if (!pCluster)
		abort();

	const t_point	sPoint = {	.x = start->x / 2,
								.y = start->y / 2,
								.distance = 0};
	clusterAdd(pCluster, &sPoint);
	if (pCluster->getClusterWeightFn)
		pCluster->weight = cluster.getClusterWeightFn(&cluster);
}

void	_initPetri(t_petri *petri, const t_art *art) {	// TODO: remove duplicates clusters
	const t_startList	*startL = art->starts;
	const size_t		HashTableSize = sqrt(art->tab.height * art->tab.width) / startL->n + 1;

	petri->vClusters = vec_create(sizeof(t_cluster));
	fTree_create(&petri->weightClusters);
	for (size_t i = 0; i < startL->n; ++i) {
		_initCluster(&startL->lStart[i], HashTableSize, petri->vClusters);
	}
	{
		t_cluster	*cluster0 = vec_get(petri->vClusters, 0);
		cluster0->ratioWeight = 10;
		cluster0->weight = 10;
	}
	for (size_t i = 0; i < startL->n; ++i) {
		t_cluster	*cluster = vec_get(petri->vClusters, i);
		printf("New cluster weight %lu\n", cluster->weight);
		fTree_append(&petri->weightClusters, cluster->weight, cluster);
	}
}

void	genTabPetri(t_art *tab) {
	t_petri	petri = {};
	_initPetri(&petri, tab);
	size_t	totalWeight = fTree_getTotalweight(&petri.weightClusters);

	const size_t	tStart = 1000;
	size_t	count[tStart] = {};

	const t_cluster	*oldCluster = NULL;
	printf("TT wieght %lu\n", totalWeight);
	while (totalWeight != 0) {
		// printf("TT wieght %lu\n", totalWeight);
		const uint64_t	indexCluster = fTree_getRandomIndex(&petri.weightClusters);
		t_cluster		*cluster = petri.weightClusters.val[indexCluster].data;
		// printf("Chose cluster %lu (%lu)\n", indexCluster, petri.weightClusters.val[indexCluster].weight);
		
		if (cluster != oldCluster) {
			oldCluster = cluster;
			// TODO: Calc wieghts pts of newCluster
		}
		
		const size_t	indexPoint = fTree_getRandomIndex(&cluster->weightPoints);
		const t_point	*point = cluster->weightPoints.val[indexPoint].data;
		// printf("Chose point %lu (%lu): ", rItem, cluster->weightPoints.val[rItem].weight);
		// printf("[%lu:%lu]", point->x, point->y);
		const uint8_t	poss = getPossibility(&tab->tab, point->x, point->y);
		const uint8_t	nPoss = __builtin_popcount(poss);
		// printf("-> nPos %u\n", nPoss);
		
		if (nPoss >= 1) {
			const int  choice = (nPoss == 1) ? __builtin_ctz(poss) : cluster->chosePossibilityFn(poss);

			_joinPoint(cluster, *point, choice, tab->tab.arr); // Maje it return a vec
			// TODO: If new point, get new point weight
			if (nPoss > 1 && oldCluster->getPointWeightFn)	// update old point weight
				fTree_update(&cluster->weightPoints, indexPoint,
					oldCluster->getPointWeightFn(point, oldCluster));
		}
		if (nPoss <= 1) {
			clusterRm(cluster, indexPoint, point);
		}
		if (cluster->ht->nItems == 0) {
			cluster->weight = 0;
			fTree_update(&petri.weightClusters, indexCluster, cluster->weight);
		} else if (cluster->getClusterWeightFn) {
			cluster->weight = cluster->getClusterWeightFn(cluster);
			fTree_update(&petri.weightClusters, indexCluster, cluster->weight);
		}
		totalWeight = fTree_getTotalweight(&petri.weightClusters);
		++count[indexCluster];
		// sleep(1);
	}
	{
		size_t tt = 0;
		for (size_t i = 0; i < petri.vClusters->size; ++i) {
			t_cluster		*cluster = petri.weightClusters.val[i].data;
			printf("%lu: %lu | %lu\n", i, count[i], cluster->weightPoints.BIT[cluster->weightPoints.cap - 1]);
			// printf("%lu: %lu\n", i, count[i]);
			tt += count[i];
		}
		printf("total: %lu\n", tt);
	}
	for (size_t i = 0; i < petri.vClusters->size; ++i) {
		t_cluster	*cluster = vec_get(petri.vClusters, i);

		// vec_destroy(cluster->vec);
		fTree_destroy(&cluster->weightPoints);
		ht_destroy(cluster->ht);
	}
	fTree_destroy(&petri.weightClusters);
	vec_destroy(petri.vClusters);
}
