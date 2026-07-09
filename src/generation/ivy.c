#include "arczn.h"

void	_getTabIvyFirst(uint8_t line[], const size_t width, const size_t nStart) {
	memset(line, 0xff, (width + 7) / 8);

	for(size_t i = 0; i < nStart - 1; ++i) {
		const size_t r = aRand(width - 1);
		line[r / 8] &= ~MASK(r % 8);
	}
}

__always_inline
int	_checkBox(size_t n, const uint8_t pLine[], const size_t width) {
	if (n >= width - 1)
		return (0);
	return (pLine[n / 8] & (MASK(n % 8)));
}

struct s_span {
	size_t start;
	size_t end;
};

__always_inline
static struct s_span	_getSpanNeighbours(const size_t n, const uint8_t pLine[], const size_t width) {
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

	for (size_t i = height * 2 - 1; i > 1;) {
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
				struct s_span s = _getSpanNeighbours(j, art->arr[i + 1], width);
				if (((size_t)aRand(100)) >= orphanPerc * 10 * (s.end - s.start) / width) {
					size_t res = aRandRange(s.start, s.end);
					art->arr[i][res / 8] |= MASK(res % 8);
				}
				j = s.end + 1;
			}
		}
	}
	_getTabIvyFirst(art->arr[0], art->width, art->nStart);
	if (art->color == CLR_GRADIENT)
		genClrIvy(art);
}

__always_inline
size_t _findParent(const uint8_t line[], const struct s_span pSpan) {
	for (size_t i = pSpan.start; i <= pSpan.end; ++i) {
		if (line[i / 8] & MASK(i % 8))
			return (i);
	}
	return (pSpan.end + 1);
}

__always_inline
static void	_genClrIvyFirst(t_clr cLine[], const size_t cSize, const uint8_t line[], const size_t lSize,
		const t_clrSet *settings) {
	for (size_t i = 0; i < cSize;) {
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
static void	_genClrIvyOdd(const uint8_t line[], t_clr dstClr[],
		const t_clr srcClr[], const t_art *art) {
	for (size_t i = 0; i < art->width; ++i) {
		if (line[i / 8] & MASK(i % 8)) {
			dstClr[2 * i] = seededNewColor(srcClr[2 * i], &art->clrSetting);
		}
	}
}

__always_inline
static void	_genClrIvyEven(const uint8_t line[], const uint8_t pLine[],
		t_clr dstClr[], const t_clr srcClr[], const t_art *art) {
	for (size_t i = 0; i < art->width;) {
		const struct s_span	arrSpan		= _getSpanNeighbours(i, line, art->width);
		const size_t		arrParent	= _findParent(pLine, arrSpan);
		const struct s_span	clrSpan		= {arrSpan.start * 2, arrSpan.end * 2};
		size_t				clrParent	= 2 * arrParent;

		if (arrParent <= arrSpan.end) {
			dstClr[clrParent] = seededNewColor(srcClr[clrParent], &art->clrSetting);
			for (size_t d = 1; d <= clrParent - clrSpan.start; ++d) {
				dstClr[clrParent - d] = seededNewColor(dstClr[clrParent - d + 1], &art->clrSetting);
			}
		}
		// else {	// Orphan
		// 	clrParent = clrSpan.start;
		// 	dstClr[clrParent] = newColor(art->clrSetting->min, art->clrSetting->max);
		// }
		for (size_t d = 1; d <= clrSpan.end - clrParent; ++d) {
			dstClr[clrParent + d] = seededNewColor(dstClr[clrParent + d - 1], &art->clrSetting);
		}
		i = arrSpan.end + 1;
	}
}

__always_inline
void	genClrIvy(t_art *art) {
	_genClrIvyFirst(art->arrClr[0], art->widthClr, art->arr[0], art->width - 1, &art->clrSetting);

	for (size_t i = 1; i < art->heightClr; i += 2) {
		_genClrIvyOdd(art->arr[i], art->arrClr[i], art->arrClr[i - 1], art);
		_genClrIvyEven(art->arr[i + 1], art->arr[i], art->arrClr[i + 1], art->arrClr[i], art);
	}
}
