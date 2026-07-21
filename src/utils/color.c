#include "arczn.h"

t_clr	newColor(const uint8_t min, const uint8_t max) {
	return ((t_clr){
		aRandRange(min, max),
		aRandRange(min, max),
		aRandRange(min, max)
	});
}


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

t_clr	seededNewColor(t_clr oldClr, const t_clrSet *set) {
	const int32_t	deltaRed = aRand(set->spanDelta) - set->delta;
	const int32_t	deltaGreen = aRand(set->spanDelta) - set->delta;
	const int32_t	deltaBlue = aRand(set->spanDelta) - set->delta;
	
	oldClr.r = _boundValue(deltaRed + oldClr.r, set->min, set->max);
	oldClr.g = _boundValue(deltaGreen + oldClr.g, set->min, set->max);
	oldClr.b = _boundValue(deltaBlue + oldClr.b, set->min, set->max);
	return (oldClr);
}

__attribute__((const, hot, always_inline)) static inline
uint8_t	_nColor_Rule(const uint8_t oldVal, const t_oneClrRules * restrict rule) {
	const int32_t	deltaRed = aRand(rule->delta * 2 + 1) - rule->delta;
	// if (deltaRed < 0)
	// 	printf("%d\n", deltaRed);

	return (_boundValue(deltaRed + oldVal, rule->min, rule->max));
}

t_clr	seededNewColor_Rules(t_clr oldCLr, const t_clrRules * restrict rules) {
	oldCLr.r = _nColor_Rule(oldCLr.r, &rules->r);
	oldCLr.g = _nColor_Rule(oldCLr.g, &rules->g);
	oldCLr.b = _nColor_Rule(oldCLr.b, &rules->b);
	return (oldCLr);
}


inline
void	newSeededNewColor_Rules(t_clr *restrict pClr,const t_clr *restrict oldCLr, const t_clrRules * restrict rules) {
	pClr->r = _nColor_Rule(oldCLr->r, &rules->r);
	pClr->g = _nColor_Rule(oldCLr->g, &rules->g);
	pClr->b = _nColor_Rule(oldCLr->b, &rules->b);
}

void	newSeededNewColor_Rules_2(t_clr *restrict pClr1, t_clr *restrict pClr2, const t_clr *restrict oldCLr, const t_clrRules * restrict rules) {
	newSeededNewColor_Rules(pClr1, oldCLr, rules);
	newSeededNewColor_Rules(pClr2, pClr1, rules);
}
