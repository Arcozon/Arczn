#include "arczn.h"
#include "petri.h"


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
uint8_t	getPossibility(uint8_t *arr[], const size_t width, const size_t height, const size_t x, const size_t y) {
	uint8_t	res = 0b0000;

	if (x != 0) { // Check left
		if (!_hasNeighbour(arr, width, height, x - 1, y))
			res |= MASK(LEFT);
	}
	if (x + 1 < width) { // Check right
		if (!_hasNeighbour(arr, width, height, x + 1, y))
			res |= MASK(RIGHT);
	}
	if (y != 0) { // Check up
		if (!_hasNeighbour(arr, width, height, x, y - 1))
			res |= MASK(UP);
	}
	if (y + 1 < height) { // Check down
		if (!_hasNeighbour(arr, width, height, x, y + 1))
			res |= MASK(DOWN);
	}
	return (res);
}


__always_inline
void	_joinPoint(t_cluster *cluster, const t_point *node, const uint8_t choice, uint8_t *tab[]) {
	const size_t	bX = node->x;
	const size_t	bY = node->y * 2;

	if (choice == UP) {
		tab[bY - 1][bX / 8] |= MASK(bX % 8);
		clusterAdd(cluster, &(t_point){bX, node->y - 1, node->origin});
	} else if (choice == DOWN) {
		tab[bY + 1][bX / 8] |= MASK(bX % 8);
		clusterAdd(cluster, &(t_point){bX, node->y + 1, node->origin});
	} else if (choice == LEFT) {
		const size_t	nX = bX - 1;
		tab[bY][nX / 8] |= MASK(nX % 8);
		clusterAdd(cluster, &(t_point){nX, node->y, node->origin});
	} else if (choice == RIGHT) {
		const size_t	nX = bX;
		tab[bY][nX / 8] |= MASK(nX % 8);
		clusterAdd(cluster, &(t_point){bX + 1, node->y, node->origin});
	} else {
		printf("Erorr\n");
	}
}

__always_inline static
t_cluster	*_initCluster(const t_start *start, const size_t HashTableSize, t_vec *vClusters) {
	t_cluster		cluster = {};
		
	cluster.weight = start->weight;
	cluster.xOrigin = start->x / 2;
	cluster.yOrigin = start->y / 2;
	cluster.ht = ht_create(HashTableSize, pointHash, pointDup, pointCmp, free);
	cluster.vec = vec_create(sizeof(t_point*));
	if (!cluster.ht || ! cluster.vec)
		abort();

	t_cluster	*pCluster = vec_add(vClusters, &cluster);
		
	const t_point	sPoint = {start->x / 2, start->y / 2, pCluster};
	clusterAdd(pCluster, &sPoint);

	return (pCluster);
}

void	_initPetri(t_petri *petri, t_art *art) {
	const t_startList	*startL = art->starts;
	const size_t	HashTableSize = sqrt(art->height * art->width) / startL->n + 1;

	petri->vClusters = vec_create(sizeof(t_cluster));
	fTree_create(&petri->weightClusters);
	{
		for (size_t i = 0; i < startL->n; ++i) {
			t_cluster	*nCluster = _initCluster(&startL->lStart[i], HashTableSize, petri->vClusters);
			
			fTree_append(&petri->weightClusters, nCluster->weight, nCluster);
		}
	}
}

void	genTabPetri(t_art *tab) {
	t_petri	petri = {};
	_initPetri(&petri, tab);
	size_t	totalWeight = petri.weightClusters.BIT[petri.weightClusters.cap - 1];

	const size_t	tStart = 50;
	size_t	count[tStart] = {};

	const t_cluster	*oldCluster = NULL;
	while (totalWeight != 0) {
		const uint64_t	index = fTree_getIndex(&petri.weightClusters, aRand(totalWeight));
		t_cluster		*cluster = petri.weightClusters.val[index].data;
		if (cluster != oldCluster) {
			oldCluster = cluster;
			// Calc wieghts newCluster
		}
		
		const size_t	rItem = aRand(cluster->ht->nItems);
		const t_point	*node = *(void **)vec_get(cluster->vec, rItem);

		const uint8_t	poss = getPossibility(tab->arr, tab->width, tab->height, node->x, node->y);
		const uint8_t	nPoss = __builtin_popcount(poss);
		
		if (nPoss >= 1) {
			// const int  choice = (nPoss == 1) ? __builtin_ctz(poss) : CPF_first(poss);
			const int  choice = (nPoss == 1) ? __builtin_ctz(poss) : CPF_ULRD(poss);

			_joinPoint(cluster, node, choice, tab->arr);
		}
		if (nPoss <= 1) {
			clusterRm(cluster, rItem, node);
			if (cluster->ht->nItems == 0) {
				fTree_update(&petri.weightClusters, index, 0);
			}
		}
		totalWeight = petri.weightClusters.BIT[petri.weightClusters.cap - 1];
		
		++count[index];
	}
	{
		size_t tt = 0;
		for (size_t i = 0; i < tStart; ++i) {
			printf("%lu: %lu\n", i, count[i]);
			tt += count[i];
		}
		printf("total: %lu\n", tt);
	}
	for (size_t i = 0; i < petri.vClusters->size; ++i) {
		t_cluster	*cluster = vec_get(petri.vClusters, i);

		vec_destroy(cluster->vec);
		ht_destroy(cluster->ht);
	}
	fTree_destroy(&petri.weightClusters);
	vec_destroy(petri.vClusters);
}
