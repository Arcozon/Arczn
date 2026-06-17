#include "arczn.h"


int	_checkBox(size_t n, uint8_t	pLine[], const size_t width) {
	if (n >= width)
		return (0);
	return (pLine[width / 8] & (MASK(width % 8)));
}

struct s_span {
	size_t start;
	size_t end;
};
struct s_span	getSpanNeighbours(const size_t n, uint8_t	pLine[], const size_t width) {
	struct s_span	res = {n, n};

	for (size_t i = n; ; --i) {
		(void)i;
		(void)width;
		(void)pLine;
	}
	return (res);
}

void	fillTabIvy(t_art *tab) {
	const size_t	height = tab->height;
	const size_t	width = tab->width;


	for (size_t i = 0; i < height * 2 - 1; ++i) {
		if (!(i & 1)){ // Horizontal Lines 
			for (size_t j = 0; j < width / 8; ++j) {
				tab->arr[i][j] = genNBit(8, tab->percent);
			}
			if (width % 8)
				tab->arr[i][width / 8] = genNBit(width % 8, tab->percent);
		} else {

		}
	}
}
