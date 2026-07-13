#include "arczn.h"
#include "hashtable.h"
#include "vector.h"
#include "fenwick_tree.h"
#include <math.h>

typedef struct {
	size_t	weight;
	uint64_t	xOrigin;
	uint64_t	yOrigin;
	t_vec	*vec;
	t_ht	*ht;
}	t_cluster;

typedef struct {
	size_t	x;
	size_t	y;
	t_cluster	*origin;
}	t_point;


typedef struct s_petri {
	t_vec	*vStart;
	t_fTree	weightStarts;
}	t_petri;


enum {	UP, LEFT, DOWN, RIGHT	};

size_t	clusterHash(const void *rPtr) {
	const t_point	*data = rPtr;
	
	return (data->x * 0x1516075A72F05 + data->y * 971);
}

void	*clusterDup(const void *_toDup) {
	const t_point *toDup = _toDup;
	t_point	*res = malloc(sizeof(t_point));

	if (res) {
		memcpy(res, toDup, sizeof(*res));
	}
	return (res);
}

bool	clusterCmp(const void *d1, const void *d2) {
	const t_point *p1 = d1;
	const t_point *p2 = d2;
	return (!(p1->x == p2->x && p1->y == p2->y));
}

void	*clusterAdd(t_cluster *cluster, const t_point *p) {
	void	*search = ht_get(cluster->ht, p);

	if (!search) {
		search = ht_add(cluster->ht, p);
		if (!search)	abort();
		vec_add(cluster->vec, &search);
	}
	return (search);
}

void	clusterRm(t_cluster *cluster, const size_t index, const void *item) {
	if (item != NULL) {
		ht_rm(cluster->ht, item);
	} else {
		ht_rm(cluster->ht, *(void **)vec_get(cluster->vec, index));
	}
	vec_rm(cluster->vec, index);
}

__always_inline
static inline bool	_hasNeighbour(uint8_t *arr[], const size_t width, const size_t height, const size_t x, const size_t _y) {
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
uint8_t	_choseOnePossibility(const uint8_t poss, const uint8_t nPoss) {	
	if (nPoss == 1)
		return (__builtin_ctz(poss));
	uint8_t	r = aRand(nPoss);
	uint8_t	i;

	for (i = 0; i < 4; ++i) {
		if (poss & MASK(i)) {
			if (!r) {
				return (i);
			}
			--r;
		}
	}
	return (i);
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

void	_initPetri(t_petri *petri, t_art *art) {
	petri->vStart = vec_create(sizeof(t_cluster));
	fTree_create(&petri->weightStarts);
	
	{
		const t_startList	*startL = art->starts;
		for (size_t i = 0; i < startL->n; ++i) {
			const t_start *start = &startL->lStart[i];
			t_cluster		cluster = {};
			
			cluster.weight = start->weight;
			cluster.xOrigin = start->x / 2;
			cluster.yOrigin = start->y / 2;
			cluster.ht = ht_create(sqrt(art->height * art->width) / startL->n + 1, clusterHash, clusterDup, clusterCmp, free);
			cluster.vec = vec_create(sizeof(t_point*));

			if (!cluster.ht || ! cluster.vec)	abort();
			vec_add(petri->vStart, &cluster);
			t_cluster	*pCluster = vec_get(petri->vStart, i);
			
			const t_point	sPoint = {start->x / 2, start->y / 2, pCluster};
			clusterAdd(pCluster, &sPoint);
			fTree_append(&petri->weightStarts, cluster.weight, pCluster);
		}
	}
}

void	genTabPetri(t_art *tab) {
	t_petri	petri = {};
	_initPetri(&petri, tab);
	size_t	totalWeight = petri.weightStarts.BIT[petri.weightStarts.cap - 1];

	const size_t	tStart = 50;
	size_t	count[tStart] = {};

	while (totalWeight != 0) {
		const uint64_t	index = fTree_getIndex(&petri.weightStarts, aRand(totalWeight));
		++count[index];
		t_cluster	*cluster = petri.weightStarts.val[index].data;
		const size_t	rItem = aRand(cluster->ht->nItems);

		const t_point	*node = *(void **)vec_get(cluster->vec, rItem);
		const uint8_t	poss = getPossibility(tab->arr, tab->width, tab->height, node->x, node->y);
		const uint8_t	nPoss = __builtin_popcount(poss);
		
		if (nPoss == 0) {
			clusterRm(cluster, rItem, node);
			if (cluster->ht->nItems == 0) {
				fTree_update(&petri.weightStarts, index, 0);
				totalWeight = petri.weightStarts.BIT[petri.weightStarts.cap - 1];
			}
			continue;
		} else {
			const int  choice = _choseOnePossibility(poss, nPoss);

			_joinPoint(cluster, node, choice, tab->arr);
			if (nPoss == 1) {
				clusterRm(cluster, rItem, node);
			}
		}
		if (cluster->ht->nItems == 0) {
			fTree_update(&petri.weightStarts, index, 0);
			totalWeight = petri.weightStarts.BIT[petri.weightStarts.cap - 1];
		}
	}
	{
		size_t tt = 0;
		for (size_t i = 0; i < tStart; ++i) {
			printf("%lu: %lu\n", i, count[i]);
			tt += count[i];
		}
		printf("total: %lu\n", tt);
	}
	for (size_t i = 0; i < petri.vStart->size; ++i) {
		t_cluster	*cluster = vec_get(petri.vStart, i);

		vec_destroy(cluster->vec);
		ht_destroy(cluster->ht);
		// free(cluster);
	}
	fTree_destroy(&petri.weightStarts);
	vec_destroy(petri.vStart);
}
