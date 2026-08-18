#include "arczn.h"

void	genTabRandom(t_art *art) {
	t_bField			*bField = &art->bField;
	const size_t	height = bField->height;
	const size_t	width = bField->width;

	for (size_t i = 0; i < height * 2 - 1; ++i) {
		for (size_t j = 0; j < width / 8; ++j) {
			bField->arr[i][j] = genNBit(8, art->percent);
		}
		if (width % 8)
			bField->arr[i][width / 8] = genNBit(width % 8, art->percent);
	}
}
