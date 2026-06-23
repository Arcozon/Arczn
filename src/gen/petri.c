#include "arczn.h"
#include "hashtable.h"
#include "vector.h"

typedef struct s_petriPoint {
	size_t	x;
	size_t	y;
}	t_petriPoint;


typedef struct s_petri {
	t_vec	*vec;
	t_ht	*ht;
}	t_petri;

enum {	UP, LEFT, DOWN, RIGHT	};

size_t	petriHash(const void *rPtr) {
	const t_petriPoint	*data = rPtr;
	
	return (data->x * 0x1516075A72F05 + data->y * 971);
}

void	*petriDup(const void *_toDup) {
	const t_petriPoint *toDup = _toDup;
	t_petriPoint	*res = malloc(sizeof(t_petriPoint));

	if (!res)	return (NULL);
	*res = *toDup;
	// printf("%lu %lu | %lu %lu\n", toDup->x, toDup->y, res->x, res->y);
	return (res);
}

bool	petriCmp(const void *d1, const void *d2) {
	const t_petriPoint *p1 = d1;
	const t_petriPoint *p2 = d2;
	return (!(p1->x == p2->x && p1->y == p2->y));
}

void	*petriAdd(t_petri *petri, const t_petriPoint *p) {
	// static int i =0;
	void	*search = ht_get(petri->ht, p);

	if (!search) {
		search = ht_add(petri->ht, p);
		vec_add(petri->vec, search);
		printf("added [%lu, %lu]\n", ((t_petriPoint *)search)->x, ((t_petriPoint *)search)->y);
		// t_petriPoint	*node = petri->vec->arr + i * sizeof(t_petriPoint);
		// printf("vec[%i] [%lu, %lu]\n", i, node->x, node->y);
		// ++i;
	} else {
		// printf("found [%lu, %lu]\n", p->x, p->y);
	}
	return (search);
}

__attribute__((always_inline))
static inline bool	_hasNeighbour(uint8_t *arr[], const size_t width, const size_t height, const size_t x, const size_t _y) {
	const size_t y = 2 * _y;
	
	if (x != 0) { // Check left
		const size_t	tX = x -1;
		if (arr[y][tX / 8] & MASK(tX % 8))
			return (true);
	} else if (x < width) {
		if (arr[y][x / 8] & MASK(x % 8))
			return (true);
	}
	if (y != 0) {
		const size_t tY = y - 1;
		if (arr[tY][x / 8] & MASK(x % 8))
			return (true);
	} else if (_y < height) {
		if (arr[y][x / 8] & MASK(x % 8))
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
	return (res);
}

void	genTabPetri(t_art *tab) {
	static const size_t	nDot = 15;
	t_petri	petri = {};

	petri.ht = ht_create((tab->width * tab->height) / 8 + 4,
				petriHash, petriDup, petriCmp, free);
	petri.vec = vec_create(sizeof(t_petriPoint));
	
	if (!petri.ht || !petri.vec) {
		free(petri.vec);
		free(petri.ht);
		return ;
	}

	printf("[%lu, %lu]\n", tab->width, tab->height);
	for (size_t i = 0; i < nDot; ++i) {
		const t_petriPoint	p = {aRand(tab->width), aRand(tab->height)};
		petriAdd(&petri, &p);
	}
	printf(" -- \n");
	for (size_t i = 0; i < petri.vec->size; ++i) {
		t_petriPoint	*node = petri.vec->arr + i * sizeof(t_petriPoint);
		
		printf("[%lu, %lu]\n", node->x, node->y);
	}
	// return ;	// EXIT
	while (petri.ht->nItems != 0) {
		const size_t	rItem = aRand(petri.ht->nItems);
		t_petriPoint	*node = petri.vec->arr + rItem * sizeof(t_petriPoint);
		
		printf("[%lu, %lu]:", node->x, node->y);
		fflush(stdout);
		const uint8_t	poss = getPossibility(tab->arr, tab->width, tab->height, node->x, node->y);
		printf("%u\n", poss);
		fflush(stdout);
		// chose one poss
		// expand
		// add new link if it has poss
		return;
	}
	free(petri.vec);
	free(petri.ht);
}
