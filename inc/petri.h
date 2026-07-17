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

struct s_cluster {
	uint64_t	xOrigin;
	uint64_t	yOrigin;

	t_vec	*vec;
	t_ht	*ht;
	size_t	weight;
	t_fTree	weightPoints;
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

enum {	UP, LEFT, DOWN, RIGHT	};

typedef uint8_t	(*t_chosePossibilityFn)(const uint8_t possibility);

uint8_t	CPF_random(const uint8_t poss);
uint8_t	CPF_first(const uint8_t poss);
uint8_t	CPF_ULRD(const uint8_t poss);


size_t	pointHash(const void *rPtr);
bool	pointCmp(const void *d1, const void *d2);
void	*pointDup(const void *_toDup);

void	*clusterAdd(t_cluster *cluster, const t_point *p);
void	clusterRm(t_cluster *cluster, const size_t index, const void *item);


#endif
