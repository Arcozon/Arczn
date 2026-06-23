#include "arczn.h"

t_clr	newColor(const uint8_t min, const uint8_t max) {
	return ((t_clr){
		aRandRange(min, max),
		aRandRange(min, max),
		aRandRange(min, max)
	});
}


t_clr	seededNewColor(t_clr oldClr, const t_clrSet set) {
	int32_t	deltaRed = aRand(set.spanDelta) - set.delta;
	int32_t	deltaGreen = aRand(set.spanDelta) - set.delta;
	int32_t	deltaBlue = aRand(set.spanDelta) - set.delta;
	
	if (deltaRed + oldClr.r <= set.min)		oldClr.r = set.min;
	else if (deltaRed + oldClr.r >= set.max)	oldClr.r = set.max;
	else										oldClr.r = deltaRed + oldClr.r;
	if (deltaGreen + oldClr.g <= set.min)		oldClr.g = set.min;
	else if (deltaGreen + oldClr.g >= set.max)	oldClr.g = set.max;
	else											oldClr.g = deltaGreen + oldClr.g;
	if (deltaBlue + oldClr.b <= set.min)		oldClr.b = set.min;
	else if (deltaBlue + oldClr.b >= set.max)	oldClr.b = set.max;
	else										oldClr.b = deltaBlue + oldClr.b;
	return (oldClr);
}
