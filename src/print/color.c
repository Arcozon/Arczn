#include "arczn.h"

void _fillFirstClrL(t_clr *clrL, const size_t sizeClrL, const uint8_t line[], const size_t sizeLine,
		const t_clrSet *settings) {
	for (size_t i = 0; i < sizeClrL;) {
		clrL[i] = newColor(settings->min, settings->max);
		++i;
		for (size_t j = i / 2; j < sizeLine; ++j) {
			if (line[j / 8] & MASK(j % 8)) {
				clrL[i] = seededNewColor(clrL[i - 1], settings);
				clrL[i + 1] = seededNewColor(clrL[i], settings);
				i += 2;
			} else {
				++i;
				break ;
			}
		}
	}
}

void	_fillClrLineOdd(const uint8_t line[], const size_t arrWidth, t_clr dstClr[],
		const t_clr srcClr[], const size_t clrWidth, const t_clrSet	*settings) {
	for (size_t i = 0; i < arrWidth; ++i) {
		if (line[i / 8] & MASK(i % 8)) {
			dstClr[2 * i] = seededNewColor(srcClr[2 * i], settings);
		}
	}
	(void)clrWidth;
}

static int	_checkBox(size_t n, const uint8_t pLine[], const size_t width) {
	if (n >= width - 1)
		return (0);
	return (pLine[n / 8] & (MASK(n % 8)));
}

struct s_span {
	size_t start;
	size_t end;
};
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

static size_t _findParent(const uint8_t line[], const struct s_span pSpan) {
	for (size_t i = pSpan.start; i <= pSpan.end; ++i) {
		if (line[i / 8] & MASK(i % 8))
			return (i);
	}
	return (pSpan.end + 1);
}

void	_fillClrLineEven(const uint8_t line[], const uint8_t prevLine[], const size_t arrWidth,
		t_clr dstClr[], const t_clr srcClr[], const size_t clrWidth, const t_clrSet	*settings) {
	for (size_t i = 0; i < arrWidth;) {
		const struct s_span	arrSpan = _getSpanNeighbours(i, line, arrWidth);
		const size_t	arrParent = _findParent(prevLine, arrSpan);
		const struct s_span	clrSpan = {arrSpan.start * 2, arrSpan.end * 2};
		size_t	clrParent = 2 * arrParent;

		if (arrParent <= arrSpan.end) {
			dstClr[clrParent] = seededNewColor(srcClr[clrParent], settings);
			for (size_t d = 1; d <= clrParent - clrSpan.start; ++d) {
				dstClr[clrParent - d] = seededNewColor(dstClr[clrParent - d + 1], settings);
			}
		}
		else {
			clrParent = clrSpan.start;
			dstClr[clrParent] = newColor(settings->min, settings->max);
		}
		for (size_t d = 1; d <= clrSpan.end - clrParent; ++d) {
			dstClr[clrParent + d] = seededNewColor(dstClr[clrParent + d - 1], settings);
		}
		i = arrSpan.end + 1;
	}
	(void)clrWidth;
}

#define FULL_ACHAR	"██"
void	_printClrLineOdd(const int fdOut, const uint8_t line[], const size_t width, const t_clr *clrL) {
	for (size_t j = 0; j + 1 < width; ++j) {
		if (line[j / 8] & MASK(j % 8)) {
			dprintf(fdOut, "\033[38;2;%d;%d;%dm"FULL_ACHAR"  ", clrL[2 * j].r, clrL[2 * j].g, clrL[2 * j].b);
		} else {
			dprintf(fdOut, "    ");
		}
	}
	{
		const size_t	tWidth = width - 1;
		if (line[tWidth / 8] & MASK(tWidth % 8)) {
			dprintf(fdOut, "\033[38;2;%d;%d;%dm"FULL_ACHAR"\n", clrL[2 * tWidth].r, clrL[2 * tWidth].g, clrL[2 * tWidth].b);
		} else {
			dprintf(fdOut, "  \n");
		}
	}
}

void	_printClrLineEven(const int fdOut, const uint8_t line[], const size_t width, const t_clr *clrL) {
	for (size_t j = 0; j < width; ++j) {
		dprintf(fdOut, "\033[38;2;%d;%d;%dm"FULL_ACHAR, clrL[2 * j].r, clrL[2 * j].g, clrL[2 * j].b);
		if (line[j / 8] & MASK(j % 8)) {
			dprintf(fdOut, "\033[38;2;%d;%d;%dm"FULL_ACHAR, clrL[2 * j + 1].r, clrL[2 * j + 1].g, clrL[2 * j + 1].b);
		} else {
			dprintf(fdOut, "  ");
		}
	}
	{
		const size_t	clrLastI = 2 * width;
		dprintf(fdOut, "\033[38;2;%d;%d;%dm"FULL_ACHAR"\n", clrL[clrLastI].r, clrL[clrLastI].g, clrL[clrLastI].b);
	}
}

void	printTabColor(const int fdOut, const t_art *tab) {
	const size_t	clrWidth = tab->width * 2 - 1;
	t_clr	*clrL[2] = {calloc(clrWidth, sizeof(*clrL)),
					calloc(clrWidth, sizeof(*clrL))};

	if (clrL[0] == NULL || clrL[1] == NULL)	return ;

	_fillFirstClrL(clrL[0], clrWidth, tab->arr[0], tab->width - 1, &tab->clrSetting);

	for (size_t i = 0; tab->arr[i]; ++i) {
		if (i & 1) {
			_printClrLineOdd(fdOut, tab->arr[i], tab->width, clrL[1]);
			_fillClrLineEven(tab->arr[i + 1], tab->arr[i], tab->width, clrL[0], clrL[1], clrWidth, &tab->clrSetting);
		} else {
			_printClrLineEven(fdOut, tab->arr[i], tab->width - 1, clrL[0]);
			if (tab->arr[i + 1])
				_fillClrLineOdd(tab->arr[i + 1], tab->width, clrL[1], clrL[0], clrWidth, &tab->clrSetting);
		}
	}
	free(clrL[0]);
	free(clrL[1]);
}
