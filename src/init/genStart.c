#include "arczn.h"
#include "hashtable.h"
#include <math.h>

// Hashtable functions
size_t	hashStart(const void *_s) {
	const t_start *s = _s;
	return (s->x * 0x1516075A72F05 + s->y * 971);
}
void	*dupStart(const void *_toDup) {
	t_start	*res = malloc(sizeof(t_start));
	if (res) memcpy(res, _toDup, sizeof(*res));
	return (res);
}
bool	cmpStart(const void *d1, const void *d2) {
	const t_start *p1 = d1;
	const t_start *p2 = d2;
	return (!(p1->x == p2->x && p1->y == p2->y));
}

__always_inline static __attribute__((const))
uint8_t	_reboundCLR(const uint8_t clr, const uint8_t min, const uint8_t max) {
	if (clr <= min)
		return (min);
	else if (clr >= max)
		return (max);
	return  (clr);
}
__always_inline static
void	_reboundRGB_Start(t_start *s) {
	s->baseClr.r = _reboundCLR(s->baseClr.r, s->rules.r.min, s->rules.r.max);
	s->baseClr.g = _reboundCLR(s->baseClr.g, s->rules.g.min, s->rules.g.max);
	s->baseClr.b = _reboundCLR(s->baseClr.b, s->rules.b.min, s->rules.b.max);
}

__always_inline static 
void	_fixOneRule(t_oneClrRules *r) {
	if (r->max < r->min) {
		size_t	max = r->max;
		r->max = r->min;
		r->min = max;
	}
	const uint8_t	range = r->max - r->min;
	if (range < r->delta) {
		r->delta = range;
	}
}

__always_inline static
void	_fixRules_Start(t_start *s) {
	_fixOneRule(&s->rules.r);
	_fixOneRule(&s->rules.g);
	_fixOneRule(&s->rules.b);
}

__always_inline __attribute__((flatten)) static
void	_fixStart(t_start *pStart, const t_tab *tab) {
	const uint64_t	w = tab->width * 2;
	const uint64_t	h = tab->height * 2;

	if (pStart->x % 2)	pStart->x -= 1;
	if (pStart->y % 2)	pStart->y -= 1;
	if (pStart->x >= w)		pStart->x = aRand(tab->width) * 2;
	if (pStart->y >= h)		pStart->y = aRand(tab->height) * 2;
	_fixRules_Start(pStart);
	_reboundRGB_Start(pStart);
}

// Retrurn 0 on success, 1 on duplicate
uint32_t fillOneStart(t_start *pStart, const t_tab *tab, size_t i, t_ht *htStart) {
	t_start start = {};
	// If already configured -> Pull
	// else
	(void)i;
	{
		start.x = aRand(tab->width) * 2;
		start.y = aRand(tab->height) * 2;
		start.weight = 2;
		start.baseClr = (t_clr){0x9 , 0xb, 0x3};
		start.rules = (t_clrRules){{0x20, 0xef, 7}, {0x16, 0x60, 4}, {0x73, 0xce, 5}};
		start.getClusterWeightFn = GCW_Linear;
		start.getPointWeightFn = GPW_distance;
		start.chosePossibilityFn = CPD_ULDR;
		start.getPossibilityMaskFn = NULL;
		start.possibilityMask = 0b1111;
	}
	if (i == 0) {
		start.x = tab->width / 3 ;
		start.y = tab->height / 3 ;
		start.weight = 20000;
		// start.chosePossibilityFn = CPD_ULDR;
		start.getPointWeightFn = GPW_test;
		start.baseClr = (t_clr){0xb5, 0x8b, 0xb0};
		start.rules = (t_clrRules){{0x20, 0xff, 14}, {0x36, 0xf0, 1}, {0x23, 0xfe, 14}};

	} else {
		start.x = tab->width / 3 + 10;
		start.y = tab->height / 3 + 10;
	}
	_fixStart(&start, tab);
	if (ht_get(htStart, &start)) { // If already in the thing
		return (1);
	}
	ht_add(htStart, &start);
	*pStart = start;
	return (0);
}

size_t	genStarts(t_nonConstArt *art) {
	t_ht *htStart = ht_create(sqrt(art->nStart) + 1, hashStart, dupStart, cmpStart, free);
	t_startList *starts = malloc(sizeof(starts->n) + sizeof(starts->lStart[0]) * art->nStart);
	if (!starts || !htStart)
		return (1);
	art->starts = starts;

	uint64_t	index = 0;
	for (size_t i = 0; i < art->nStart; ++i) {
		if (!fillOneStart(&starts->lStart[index], &art->tab, i, htStart))
			++index;
	}
	starts->n = index;
	art->nStart = index;

	for (size_t i = 0; i < art->nStart; ++i) {
		const t_clr			bClr = starts->lStart[i].baseClr;
		const t_clrRules	rules = starts->lStart[i].rules;
		printf("%lu: [%lu, %lu] #%2X%2X%2X\n", i, starts->lStart[i].x, starts->lStart[i].y, bClr.r, bClr.g, bClr.b);
		printf("	R: [%u-%u](%u)\n", rules.r.min, rules.r.max, rules.r.delta);
		printf("	G: [%u-%u](%u)\n", rules.g.min, rules.g.max, rules.g.delta);
		printf("	B: [%u-%u](%u)\n", rules.b.min, rules.b.max, rules.b.delta);
	}
	ht_destroy(htStart);
	return (0);
}

// #AF69EE
// #46923c
