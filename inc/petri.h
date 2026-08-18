#ifndef PETRI_H
# define PETRI_H

#include "types.h"
#include "hashtable.h"
#include "vector.h"
#include "fenwick_tree.h"
#include <math.h>

# ifndef M_PI
#  define M_PI		3.14159265358979323846
# endif

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
	
	const t_removePointFn			removePointFn;
	
	const uint8_t					choseLastPoint:1;
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

size_t	pointHash(const void *rPtr);
bool	pointCmp(const void *d1, const void *d2);
void	*pointDup(const void *_toDup);

void	*clusterAdd(t_cluster *cluster, const t_point *p);
void	clusterRm(t_cluster *cluster, const size_t index, const void *item);

// Get Cluster Weight
t_getClusterWeightSig	GCW_Linear;

// Get Point Weight
t_getPointWeightSig	GPW_One;
t_getPointWeightSig	GPW_distance;
t_getPointWeightSig	GPW_test;
t_getPointWeightSig	GPW_rectangle;
t_getPointWeightSig	GPW_distance_ULDR;
	
// Get Point Possibility Mask
t_getPossibilityMaskSig	GPM_Angle;

// Chose Possibility Direction
t_chosePossibilitySig	CPD_Test;
t_chosePossibilitySig	CPD_random;
t_chosePossibilitySig	CPD_first;
t_chosePossibilitySig	CPD_binary;
t_chosePossibilitySig	CPD_angle;
t_chosePossibilitySig	CPD_ULRD;
t_chosePossibilitySig	CPD_ULDR;

// Remove Point
t_removePointSig	RP_test;

#endif
