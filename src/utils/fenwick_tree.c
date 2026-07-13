#include "fenwick_tree.h"
#include <stdio.h>


uint64_t _fTree_getSum(const uint64_t BIT[], size_t index) {
	const uint64_t	*BIT0 = &BIT[-1];
	uint64_t	sum = 0;
	
	++index;
	while (index > 0) {
		sum += BIT0[index];
		index -= index & (-index);
	}
	return (sum);
}

uint32_t	fTree_create(t_fTree *tree) {
	t_fTree	nTree = {.cap = FENWICK_TREE_DEFAULT_SIZE, .n = 0};

	nTree.BIT = calloc(nTree.cap, sizeof(tree->BIT[0]));
	nTree.val = calloc(nTree.cap, sizeof(tree->val[0]));
	if (!nTree.BIT || !nTree.val) {
		free(nTree.BIT);
		free(nTree.val);
		return (1);
	}
	*tree = nTree;
	return (0);
}

void	fTree_destroy(t_fTree *pTree) {
	free(pTree->BIT);
	free(pTree->val);
	*pTree = (t_fTree){0};
}

uint32_t	fTree_append(t_fTree *tree, const uint64_t weight, void *data) {
	if (tree->cap <= tree->n) {
		t_fTree	nTree = {.cap = 2 * tree->cap, .n = tree->n};
		
		nTree.BIT = realloc(tree->BIT, nTree.cap * sizeof(tree->BIT[0]));
		nTree.val = realloc(tree->val, nTree.cap * sizeof(tree->val[0]));
		if (!nTree.BIT || !nTree.val) {
			free(nTree.BIT);
			free(nTree.val);
			fTree_destroy(tree);
			return (1);
		}
		bzero(&nTree.val[tree->cap], tree->cap * sizeof(nTree.val[0]));
		bzero(&nTree.BIT[tree->cap], tree->cap * sizeof(nTree.BIT[0]));
		// printf(" -- %lu(%lu) -- %lu\n", tree->cap - 1, nTree.BIT[tree->cap - 1], 2 * tree->cap - 1);
		nTree.BIT[tree->cap * 2 - 1] = nTree.BIT[tree->cap - 1];
		*tree = nTree;
	}
	// printf("data")
	tree->val[tree->n].data = data;
	fTree_update(tree, tree->n, weight);
	++tree->n;
	return (0);
}

void	fTree_update(t_fTree *tree, uint64_t index, const uint64_t nWeight) {
	const uint64_t	delta = nWeight - tree->val[index].weight;
	uint64_t	*BIT0 = &tree->BIT[-1];
	
	tree->val[index].weight = nWeight;
	++index;
	
	while (index <= tree->cap) {
		BIT0[index] += delta;
		index += index & (-index);
	}
}

uint64_t fTree_getIndex(const t_fTree *tree, uint64_t weight) {
	const uint64_t	*BIT0 = &tree->BIT[-1];
	size_t   index = 0;
    size_t   bitmask = tree->cap;	// CAP IS A POWER OF 2

	if (tree->cap == 0) {
		printf("Fenwick tree cap == 0\n");
		abort();
	}
	if (weight >= BIT0[tree->cap]) {
		return (tree->n - 1);
	}

    while (bitmask != 0) {
        size_t next_index = index + bitmask;
        if (next_index <= tree->cap && BIT0[next_index] <= weight) {
            index = next_index;
            weight -= BIT0[index];
        }
        bitmask >>= 1;
    }
    return (index);
}
