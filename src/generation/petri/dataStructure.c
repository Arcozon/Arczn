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
	fTree_remove(&cluster->weightPoints, index);
	ht_rm(cluster->ht, item);
}
