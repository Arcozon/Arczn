#include "arczn.h"

uint8_t	genNBit(const uint8_t nBit, const uint8_t percent) {
	uint8_t	res = 0;

	for (uint8_t i = 0; i < nBit; ++i) {
		if (aRand(100) < percent)
			res |= MASK(i);
	}
	return (res);
}

void	genTabRandom(t_art *tab) {
	const size_t	height = tab->height;
	const size_t	width = tab->width;

	for (size_t i = 0; i < height * 2 - 1; ++i) {
		for (size_t j = 0; j < width / 8; ++j) {
			tab->arr[i][j] = genNBit(8, tab->percent);
		}
		if (width % 8)
			tab->arr[i][width / 8] = genNBit(width % 8, tab->percent);
	}
}
