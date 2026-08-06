#ifndef PETRI_H
# define PETRI_H

#include "types.h"
#include "hashtable.h"
#include "vector.h"
#include "fenwick_tree.h"
#include <math.h>



struct s_cluster {
	const uint64_t	xOrigin;
	const uint64_t	yOrigin;

	t_ht	*ht;
	t_fTree	weightPoints;
	
	size_t	ratioWeight;
	size_t	weight;
	const t_getClusterWeightFn		getClusterWeightFn;
	
	const uint8_t	possibilityMask;
	const t_getPossibilityMaskFn	getPossibilityMaskFn;

	const t_getPointWeightFn		getPointWeightFn;
	const t_chosePossibilityFn		chosePossibilityFn;
};

struct s_point {
	size_t	x;
	size_t	y;
	size_t	distance;
};


struct s_petri {
	t_vec	*vClusters;
	t_fTree	weightClusters;
};

enum {	UP, LEFT, DOWN, RIGHT, NONE};

uint64_t	GCW_Linear(const t_cluster *cluster);

uint64_t	GPW_One(const t_point *point, const t_cluster *cluster);
uint64_t	GPW_distance(const t_point *point, const t_cluster *cluster);
uint64_t	GPW_distance_UP(const t_point *point, const t_cluster *cluster);
uint64_t	GPW_rectangle(const t_point *point, const t_cluster *cluster);
uint64_t	GPW_distance_ULDR(const t_point *point, const t_cluster *cluster);
	
	
uint8_t	CPD_random(const uint8_t poss);
uint8_t	CPD_first(const uint8_t poss);
uint8_t	CPD_ULRD(const uint8_t poss);
uint8_t	CPD_ULDR(const uint8_t poss);

size_t	pointHash(const void *rPtr);
bool	pointCmp(const void *d1, const void *d2);
void	*pointDup(const void *_toDup);

void	*clusterAdd(t_cluster *cluster, const t_point *p);
void	clusterRm(t_cluster *cluster, const size_t index, const void *item);


#endif
