#ifndef FENWICK_TREE_H
# define FENWICK_TREE_H

#include <strings.h>
#include <stdlib.h>

#include "types.h"
#include "random.h"

# define FENWICK_TREE_DEFAULT_SIZE	2UL

typedef struct s_fTree		t_fTree;
typedef struct s_FT_data	t_FT_data;

struct s_FT_data {
	uint64_t	weight;
	void		*data;
};

struct s_fTree {
	uint64_t	n;
	uint64_t	cap;
	uint64_t	*BIT;
	t_FT_data	*val;
};


uint32_t	fTree_create(t_fTree *tree);
void		fTree_destroy(t_fTree *tree);

uint32_t	fTree_append(t_fTree *tree, uint64_t weight, void *data);
void		fTree_remove(t_fTree *tree, uint64_t index);
void		fTree_update(t_fTree *tree, uint64_t index, const uint64_t nWeight);

uint64_t fTree_getIndex(const t_fTree *tree, uint64_t weight);
uint64_t fTree_getRandomIndex(const t_fTree *tree);

#endif
