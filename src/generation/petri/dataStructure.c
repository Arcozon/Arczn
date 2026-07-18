#include "petri.h"
#include "stdio.h"

size_t	pointHash(const void *rPtr) {
	const t_point	*data = rPtr;
	
	return (data->x * 0x1516075A72F05 + data->y * 971);
}

void	*pointDup(const void *_toDup) {
	const t_point *toDup = _toDup;
	t_point	*res = malloc(sizeof(t_point));

	if (res) {
		memcpy(res, toDup, sizeof(*res));
	}
	return (res);
}

bool	pointCmp(const void *d1, const void *d2) {
	const t_point *p1 = d1;
	const t_point *p2 = d2;
	return (!(p1->x == p2->x && p1->y == p2->y));
}

void	*clusterAdd(t_cluster *cluster, const t_point *p) {
	void	*search = ht_get(cluster->ht, p);

	if (!search) {
		search = ht_add(cluster->ht, p);
		if (!search)	abort();
		// vec_add(cluster->vec, &search);
		fTree_append(&cluster->weightPoints, cluster->getPointWeightFn(search, cluster), search);
	} else {
		// Update weight
	}
	return (search);
}

void	clusterRm(t_cluster *cluster, const size_t index, const void *item) {
	// const t_point	*point = item;
	// printf("removing [%lu:%lu]\n", point->x, point->y);
	// } else {
	// 	ht_rm(cluster->ht, *(void **)vec_get(cluster->vec, index));
	// }
	// vec_rm(cluster->vec, index);
	
	fTree_remove(&cluster->weightPoints, index);
	// fTree_update(&cluster->weightPoints, index, 0);
	// cluster->weightPoints.val[index].data = 0;
	

	// {
	// 	t_fTree *t = &cluster->weightPoints;
	// 	for (size_t i = 0; i < t->n; ++i ){
	// 		t_point *p = t->val[i].data;
	// 		if (p) {
	// 			printf("%lu: [%lu:%lu] -> %lu\n", i, p->x, p->y, t->val[i].weight);
	// 		}
	// 	}
	// }
	ht_rm(cluster->ht, item);

}
