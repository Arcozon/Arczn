#include "arczn.h"



void	genTabRandom(t_art *art) {
	t_tab			*tab = &art->tab;
	const size_t	height = tab->height;
	const size_t	width = tab->width;

	for (size_t i = 0; i < height * 2 - 1; ++i) {
		for (size_t j = 0; j < width / 8; ++j) {
			tab->arr[i][j] = genNBit(8, art->percent);
		}
		if (width % 8)
			tab->arr[i][width / 8] = genNBit(width % 8, art->percent);
	}
}
