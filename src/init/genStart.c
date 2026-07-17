#include "arczn.h"

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
	if (r->max < r->min)
		r->max = r->min;
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

__always_inline static
void	_fixCoordinate_Start(t_start *s, const size_t w, const size_t h) {
	if (s->x >= w)
		s->x = w -1;
	if (s->y >= h)
		s->y = h -1;
}

__always_inline static
void	_fixStarts(t_start starts[], const size_t nStart, const t_nonConstArt *art) {
	const uint64_t	w = art->width * 2 - 1;
	const uint64_t	h = art->height * 2 - 1;

	for (size_t i = 0; i < nStart; ++i) {
		_fixCoordinate_Start(&starts[i], w, h);
		_fixRules_Start(&starts[i]);
		_reboundRGB_Start(&starts[i]);
	}
}

size_t	genStarts(t_nonConstArt *art) {
	t_startList *starts = malloc(sizeof(starts->n) + sizeof(starts->lStart[0]) * art->nStart);
	if (!starts)
		return (1);
	art->starts = starts;
	starts->n = art->nStart;
	for (size_t i = 0; i < art->nStart; ++i) {
		starts->lStart[i] = (t_start){
			.x = aRand(art->width) * 2,
			.y = aRand(art->height) * 2,
			.weight = 3,
			.baseClr = {0x96,0xb2, 0x3c},
			.rules = (t_clrRules){{0x40, 0xbf, 5}, {0x36, 0x80, 2}, {0x83, 0xce, 1}}
			// .rules = (t_clrRules){{0x60, 0xff, 10}, {0x49, 0x9f, 4}, {0x77, 0x75, 9}}
		};
	}
	if (art->nStart > 1) {
		starts->lStart[1].rules = (t_clrRules){{0x9f, 0xff, 10}, {0x69, 0x92, 1}, {0x3c, 0x5e, 1}};
		starts->lStart[1].weight = 200;
	}
	
	_fixStarts(starts->lStart, starts->n, art);

	for (size_t i = 0; i < art->nStart; ++i) {
		const t_clr			bClr = starts->lStart[i].baseClr;
		const t_clrRules	rules = starts->lStart[i].rules;
		printf("%lu: [%lu, %lu] #%2X%2X%2X\n", i, starts->lStart[i].x, starts->lStart[i].y, bClr.r, bClr.g, bClr.b);
		printf("	R: [%u-%u](%u)\n", rules.r.min, rules.r.max, rules.r.delta);
		printf("	G: [%u-%u](%u)\n", rules.g.min, rules.g.max, rules.g.delta);
		printf("	B: [%u-%u](%u)\n", rules.b.min, rules.b.max, rules.b.delta);
	}
	return (0);
}

// #AF69EE
// #46923c
