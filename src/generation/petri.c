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
	return (res);
}

bool	petriCmp(const void *d1, const void *d2) {
	const t_petriPoint *p1 = d1;
	const t_petriPoint *p2 = d2;
	return (!(p1->x == p2->x && p1->y == p2->y));
}

void	*petriAdd(t_petri *petri, t_petriPoint p) {
	void	*search = ht_get(petri->ht, &p);

	if (!search) {
		search = ht_add(petri->ht, &p);
		vec_add(petri->vec, search);
	}
	return (search);
}

void	petriRm(t_petri *petri, const size_t index, const void *item) {
	if (item != NULL) {
		ht_rm(petri->ht, item);
	} else {
		ht_rm(petri->ht, vec_get(petri->vec, index));
	}
	vec_rm(petri->vec, index);
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
void	_joinPointColor(t_art *art, const t_petriPoint *node, const int dX, const int dY) {
	const size_t	sX = node->x * 2;
	const size_t	sY = node->y * 2;

	if (art->color == CLR_GRADIENT && 0) {
		art->arrClr[sY + dY][sX + dX] = seededNewColor(art->arrClr[sY][sX], &art->clrSetting);
		art->arrClr[sY + 2 * dY][sX + 2 * dX] = seededNewColor(art->arrClr[sY + dY][sX + dX], &art->clrSetting);
	}
}

__always_inline
void	_joinPoint(t_petri *petri, const t_petriPoint *node, const uint8_t choice, uint8_t *tab[], t_art *art) {
	const size_t	bX = node->x;
	const size_t	bY = node->y * 2;

	if (choice == UP) {
		tab[bY - 1][bX / 8] |= MASK(bX % 8);
		petriAdd(petri, (t_petriPoint){bX, node->y - 1});
		_joinPointColor(art, node, 0, -1);
	} else if (choice == DOWN) {
		tab[bY + 1][bX / 8] |= MASK(bX % 8);
		petriAdd(petri, (t_petriPoint){bX, node->y + 1});
		_joinPointColor(art, node, 0, 1);
	} else if (choice == LEFT) {
		const size_t	nX = bX - 1;
		tab[bY][nX / 8] |= MASK(nX % 8);
		petriAdd(petri, (t_petriPoint){nX, node->y});
		_joinPointColor(art, node, -1, 0);
	} else if (choice == RIGHT) {
		const size_t	nX = bX;
		tab[bY][nX / 8] |= MASK(nX % 8);
		petriAdd(petri, (t_petriPoint){bX + 1, node->y});
		_joinPointColor(art, node, 1, 0);
	} else {
		printf("Erorr\n");
	}
}

void	genTabPetri(t_art *tab) {
	t_petri	petri = {};

	petri.ht = ht_create((tab->width * tab->height) / 8 + 4,
				petriHash, petriDup, petriCmp, free);
	petri.vec = vec_create(sizeof(t_petriPoint));
	
	if (!petri.ht || !petri.vec) {
		vec_destroy(petri.vec);
		ht_destroy(petri.ht);
		return ;
	}
	{
		const t_startList	*startL = tab->starts;
		for (size_t i = 0; i < startL->n; ++i) {
			const t_petriPoint	p = {startL->lStart[i].x / 2, startL->lStart[i].y / 2};
			petriAdd(&petri, p);
			if (tab->color == CLR_GRADIENT && 0)
				tab->arrClr[p.y * 2][p.x * 2] = newColor(tab->clrSetting.min, tab->clrSetting.max);
		}
	}
	while (petri.ht->nItems != 0) {
		const size_t	rItem = aRand(petri.ht->nItems);
		t_petriPoint	node = *(t_petriPoint *)vec_get(petri.vec, rItem);
		const uint8_t	poss = getPossibility(tab->arr, tab->width, tab->height, node.x, node.y);
		const uint8_t	nPoss = __builtin_popcount(poss);
		
		if (nPoss == 0) {
			petriRm(&petri, rItem, &node);
			continue;
		} else {
			const int  choice = _choseOnePossibility(poss, nPoss);
			
			_joinPoint(&petri, &node, choice, tab->arr, tab);
			if (nPoss == 1) {
				petriRm(&petri, rItem, &node);
			}
		}
	}
	vec_destroy(petri.vec);
	ht_destroy(petri.ht);
}
