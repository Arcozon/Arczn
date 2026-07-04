#include "arczn.h"

static int	_checkBox(size_t n, const uint8_t pLine[], const size_t width) {
	if (n >= width - 1)
		return (0);
	return (pLine[n / 8] & (MASK(n % 8)));
}

struct s_span {
	size_t start;
	size_t end;
};

static struct s_span	getSpanNeighbours(const size_t n, const uint8_t pLine[], const size_t width) {
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

void	genClrIvy(t_art *art);
void	genTabIvy(t_art *art) {
	const size_t	height = art->height;
	const size_t	width = art->width;
	const size_t	orphanPerc = art->orphanPercent;

	for (size_t i = height * 2 - 1; i > 0;) {
		--i;
		if (!(i & 1)){ // Horizontal Lines 
			const size_t	tWidth = width - 1;
			for (size_t j = 0; j < tWidth / 8; ++j) {
				art->arr[i][j] = genNBit(8, art->percent);
			}
			if (tWidth % 8)
				art->arr[i][tWidth / 8] = genNBit(tWidth % 8, art->percent);
		} else {
			for (size_t j = 0; j < width;) {
				struct s_span s = getSpanNeighbours(j, art->arr[i + 1], width);
				if (((size_t)aRand(100)) >= orphanPerc * 10 * (s.end - s.start) / width) {
					size_t res = aRandRange(s.start, s.end);
					art->arr[i][res / 8] |= MASK(res % 8);
				}
				j = s.end + 1;
			}
		}
	}
	if (art->arrClr)
		genClrIvy(art);
}


__always_inline
static void	_genClrIvyFirst(t_clr cLine[], const size_t cSize, const uint8_t line[], const size_t lSize,
		const t_clrSet *settings) {
	printf("%lu\n", cSize);
	for (size_t i = 0; i < cSize;) {
		printf("%lu\n", i);
		cLine[i] = newColor(settings->min, settings->max);
		++i;
		for (size_t j = i / 2; j < lSize; ++j) {
			if (line[j / 8] & MASK(j % 8)) {
				cLine[i] = seededNewColor(cLine[i - 1], settings);
				cLine[i + 1] = seededNewColor(cLine[i], settings);
				i += 2;
			} else {
				++i;
				break ;
			}
		}
	}
}

__always_inline
static void	_genClrIvyOdd(t_art *art) {
	(void)art;
}

__always_inline
static void	_genClrIvyEven(t_art *art) {
	(void)art;
}

void	genClrIvy(t_art *art) {
	_genClrIvyFirst(art->arrClr[0], art->widthClr, art->arr[0], art->width, &art->clrSetting);
}
