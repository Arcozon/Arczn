#ifndef PETRI_H
# define PETRI_H

#include "types.h"
#include "hashtable.h"
#include "vector.h"
#include "fenwick_tree.h"
#include <math.h>


typedef struct s_cluster	t_cluster;
typedef struct s_point	t_point;
typedef struct s_petri	t_petri;

typedef uint8_t		(*t_chosePossibilityFn)(const uint8_t possibility);
typedef uint64_t	(*t_getPointWeightFn)(const t_point *point, const t_cluster *cluster);

struct s_cluster {
	const uint64_t	xOrigin;
	const uint64_t	yOrigin;

	t_vec	*vec;
	t_ht	*ht;
	t_fTree	weightPoints;
	size_t	weight;
	// size_t	ratioWeight;
	// size_t	baseWeight;


	const t_chosePossibilityFn	chosePossibilityFn;
	const t_getPointWeightFn	getPointWeightFn;
};

struct s_point {
	size_t	x;
	size_t	y;
	// size_t	distance;
	t_cluster	*origin;	// remove
};


struct s_petri {
	t_vec	*vClusters;
	t_fTree	weightClusters;
};

enum {	UP, LEFT, DOWN, RIGHT, NONE};


uint8_t	CPF_random(const uint8_t poss);
uint8_t	CPF_first(const uint8_t poss);
uint8_t	CPF_ULRD(const uint8_t poss);

uint64_t	GPW_One(const t_point *point, const t_cluster *cluster);
uint64_t	GPW_distance(const t_point *point, const t_cluster *cluster);

size_t	pointHash(const void *rPtr);
bool	pointCmp(const void *d1, const void *d2);
void	*pointDup(const void *_toDup);

void	*clusterAdd(t_cluster *cluster, const t_point *p);
void	clusterRm(t_cluster *cluster, const size_t index, const void *item);


#endif
