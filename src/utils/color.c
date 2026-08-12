#include "arczn.h"

__attribute__((const, hot, always_inline)) static inline
uint8_t	_boundValue(const int32_t nVal, const uint8_t min, const uint8_t max) {
	if (nVal <= min) {
		return (min);
	} else if (nVal >= max) {
		return (max);
	} else {
		return (nVal);
	}
}

__attribute__((const, hot, always_inline)) static inline
uint8_t	_seededColorRule(const uint8_t oldVal, const t_oneClrRules * restrict rule) {
	const int32_t	delta = aRand(rule->delta * 2 + 1) - rule->delta;

	return (_boundValue(delta + oldVal, rule->min, rule->max));
}

t_clr	seededNewColor_Rules(t_clr oldCLr, const t_clrRules * restrict rules) {
	oldCLr.r = _seededColorRule(oldCLr.r, &rules->r);
	oldCLr.g = _seededColorRule(oldCLr.g, &rules->g);
	oldCLr.b = _seededColorRule(oldCLr.b, &rules->b);
	return (oldCLr);
}


inline
void	newSeededNewColor_Rules(t_clr *restrict pClr,const t_clr *restrict oldCLr, const t_clrRules * restrict rules) {
	pClr->r = _seededColorRule(oldCLr->r, &rules->r);
	pClr->g = _seededColorRule(oldCLr->g, &rules->g);
	pClr->b = _seededColorRule(oldCLr->b, &rules->b);
}

void	newSeededNewColor_Rules_2(t_clr *restrict pClr1, t_clr *restrict pClr2, const t_clr *restrict oldCLr, const t_clrRules * restrict rules) {
	newSeededNewColor_Rules(pClr1, oldCLr, rules);
	newSeededNewColor_Rules(pClr2, pClr1, rules);
}
