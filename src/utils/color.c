#include "arczn.h"

t_clr	newColor(const uint8_t min, const uint8_t max) {
	return ((t_clr){
		aRandRange(min, max),
		aRandRange(min, max),
		aRandRange(min, max)
	});
}


__attribute__((const, hot, always_inline)) static inline
uint8_t	_boundValue(const uint32_t nVal, const uint8_t min, const uint8_t max) {
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
