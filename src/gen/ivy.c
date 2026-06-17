#include "arczn.h"


int	_checkBox(size_t n, const uint8_t pLine[], const size_t width) {
	if (n >= width - 1)
		return (0);
	return (pLine[n / 8] & (MASK(n % 8)));
}

struct s_span {
	size_t start;
	size_t end;
};
struct s_span	getSpanNeighbours(const size_t n, const uint8_t pLine[], const size_t width) {
	size_t	start;
	size_t	end;

	for (start = n - 1; ; --start) {
		if (!_checkBox(start, pLine, width))
			break;
	}
	for (end = n; ; ++end) {
		if (!_checkBox(end, pLine, width))
			break;
	}
	return ((struct s_span){start + 1, end});
}

void	genTabIvy(t_art *tab) {
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
			for (size_t j = 0; j < width;) {
				struct s_span s = getSpanNeighbours(j, tab->arr[i - 1], width);
				// printf("%lu Span [%lu]: %lu-%lu (%lu)\n", i - 1, j, s.start, s.end, s.end - s.start);
				size_t res = rand() % (s.end - s.start + 1) + s.start;
				tab->arr[i][res / 8] |= MASK(res % 8);
				j = s.end + 1;
				// break;
			}
		}
	}
}
