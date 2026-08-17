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
void	_fixStart(t_start *pStart, const t_bField *bField) {
	if (pStart->x >= bField->width)
		pStart->x = aRand(bField->width);
	if (pStart->y >= bField->height)
		pStart->y = aRand(bField->height);
	_fixRules_Start(pStart);
	_reboundRGB_Start(pStart);
	if (pStart->chosePossibilityFn == NULL)
		pStart->chosePossibilityFn = CPD_random;
}

// Retrurn 0 on success, 1 on duplicate
uint32_t fillOneStart(t_start *pStart, const t_bField *bField, size_t i, t_ht *htStart) {
	t_start start = {};
	// If already configured -> Pull
	// else
	(void)i;
	if (i == 0) {
	// 	start.x = aRand(bField->width);
	// 	start.y = aRand(bField->height);

		start.x = bField->width / 2;
		start.y = bField->height / 2;

		start.weight = 1;
		start.baseClr = (t_clr){0x90 , 0xb0, 0x3e};
		start.rules = (t_clrRules){{0xb0, 0xff, 3}, {0x66, 0xf0, 9}, {0xb0, 0xff, 5}};
		start.getClusterWeightFn = 0;
		start.getPointWeightFn = 0;
		start.chosePossibilityFn = 0;
		start.getPossibilityMaskFn = 0;
		start.possibilityMask = MASK(UP) | MASK(LEFT) | MASK(DOWN) | MASK(RIGHT);
		start.removePointFn = 0;
		start.choseLastPoint = true;

	} else
	{
		start.x = 150 + 90;
		start.y = 150;

		start.weight = 40000;
		start.baseClr = (t_clr){0x90 , 0xb0, 0x3e};
		start.rules = (t_clrRules){{0x60, 0xaf, 6}, {0x26, 0x40, 7}, {0x73, 0xcf, 4}};
		start.getClusterWeightFn = 0;
		// start.getPointWeightFn = GPW_test;
		start.chosePossibilityFn = CPD_Test;
		start.getPossibilityMaskFn = GPM_Angle;
		start.possibilityMask = MASK(UP) | MASK(LEFT) | MASK(DOWN) | MASK(RIGHT);
		// start.removePointFn = RP_test;
		// start.choseLastPoint = true;
	}
	_fixStart(&start, bField);
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
		if (!fillOneStart(&starts->lStart[index], &art->bField, i, htStart))
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
