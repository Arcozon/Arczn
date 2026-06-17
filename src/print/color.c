#include "arczn.h"

typedef struct s_clr	t_clr;
struct s_clr {
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
};

__attribute__((always_inline, pure))
static inline uint8_t	_bound(const uint8_t val, const uint8_t min, const uint8_t max) {
	if (val < min)	return (min);
	if (val > max)	return (max);
	return	(val);
}

t_clr	newColor(const uint8_t min, const uint8_t max) {
	return ((t_clr){
		_bound(rand() % 256, min, max),
		_bound(rand() % 256, min, max),
		_bound(rand() % 256, min, max)});
}

t_clr	seededNewColor(struct s_clr oldClr, const t_clrSet settings) {
	return (oldClr);
	(void)settings;
}

void _fillFirstClrL(t_clr *clrL, const size_t sizeClrL, const uint8_t line[], const size_t sizeLine,
	const t_clrSet settings) {
	for (size_t i = 0; i < sizeClrL;) {
		clrL[i] = newColor(settings.min, settings.max);
		++i;
		for (size_t j = i / 2; j < sizeLine; ++j) {
			if (line[j / 8] & MASK(j % 8)) {
				clrL[i] = newColor(settings.min, settings.max);
				clrL[i + 1] = newColor(settings.min, settings.max);
				i += 2;
			} else
				break ;
		}
	}
}
#define FULL_ACHAR	"██"
void	_printClrLineOdd(const uint8_t line[], const size_t width, const t_clr *clrL) {
	for (size_t j = 0; j + 1 < width; ++j) {
		if (line[j / 8] & MASK(j % 8)) {
			printf("\033[38;2;%d;%d;%dm"FULL_ACHAR"  ", clrL[2 * j].r, clrL[2 * j].g, clrL[2 * j].b);
		} else {
			printf("    ");
		}
	}
	{
		const size_t	tWidth = width - 1;
		if (line[tWidth / 8] & MASK(tWidth % 8)) {
			printf("\033[38;2;%d;%d;%dm"FULL_ACHAR"\n", clrL[2 * tWidth].r, clrL[2 * tWidth].g, clrL[2 * tWidth].b);
		} else {
			printf("  \n");
		}
	}
}

void	_printClrLineEven(const uint8_t line[], const size_t width, const t_clr *clrL) {
	for (size_t j = 0; j < width; ++j) {
		printf("\033[38;2;%d;%d;%dm"FULL_ACHAR, clrL[2 * j].r, clrL[2 * j].g, clrL[2 * j].b);
		if (line[j / 8] & MASK(j % 8)) {
			printf("\033[38;2;%d;%d;%dm"FULL_ACHAR, clrL[2 * j + 1].r, clrL[2 * j + 1].g, clrL[2 * j + 1].b);
		} else {
			printf("  ");
		}
	}
	{
		const size_t	tWidth = width - 1;
		printf("\033[38;2;%d;%d;%dm"FULL_ACHAR"\n", clrL[2 * tWidth - 1].r, clrL[2 * tWidth - 1].g, clrL[2 * tWidth - 1].b);
	}
}

void	printTabColor(const int fdOut, const t_art tab) {
	t_clr	*clrL[2] = {calloc(tab.width * 2 - 1, sizeof(*clrL)),
					calloc(tab.width * 2 - 1, sizeof(*clrL))};

	if (clrL[0] == NULL || clrL[1] == NULL)	return ;
	_fillFirstClrL(clrL[0], tab.width * 2 - 1, tab.arr[0], tab.width - 1, tab.clrSetting);
	for (size_t i = 0; tab.arr[i]; ++i) {
		if (i & 1) {
			_printClrLineOdd(tab.arr[i], tab.width, clrL[1]);
		} else {
			_printClrLineEven(tab.arr[i], tab.width - 1, clrL[0]);
		}
	}
	fflush(stdout);
	printTab(fdOut, tab);
	(void)fdOut;
}
