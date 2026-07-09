#include "arczn.h"

__always_inline
void	_applyClrEven(t_clr lClr[], const uint8_t line[], const size_t width) {
	for (size_t i = 0; i < width - 1; ++i) {
		if (!(line[i / 8] & MASK(i % 8))) {
			const size_t	j = 2 * i + 1;
			lClr[j] = (t_clr){0};
		}
	}
}

__always_inline
void	_applyClrOdd(t_clr lClr[], const uint8_t line[], const size_t width) {
	for (size_t i = 0; i < width - 1; ++i) {
		const size_t	j = 2 * i;
		if (!(line[i / 8] & MASK(i % 8))) {
			lClr[j] = (t_clr){0};
		}
		lClr[j + 1] = (t_clr){0};
	}
	const size_t	i = width - 1;
	if (!(line[i / 8] & MASK(i % 8))) {
		lClr[2 * i] = (t_clr){0};
	}
}

__always_inline
__attribute__((hot, const))
uint8_t	_addClr(const uint8_t c, const uint32_t i)  {
	if (i + c > 255)
		return (255);
	return (i + c);
}

void	_applyClr_4b4(t_clr *clr[], const uint8_t *arr[], const size_t w, const size_t h) {
	printf("%lux%lu", 2 * (w - 1), h);
	for (size_t i = 0; i < h - 1; i += 2) {
		for (size_t j = 0; j < w - 1; ++j) {
			const size_t	J = 2 * j;
			uint16_t	count = 1;
			t_iClr		buff = {clr[i + 1][J + 1].r, clr[i + 1][J + 1].g, clr[i + 1][J + 1].b};
			clr[i + 1][J + 1] = (t_clr){0};
			if (!(arr[i][j / 8] & (MASK(j % 8)))) {
				buff.r += clr[i][J + 1].r;
				buff.g += clr[i][J + 1].g;
				buff.b += clr[i][J + 1].b;
				++count;
			}	
			if (!(arr[i + 1][j / 8] & (MASK(j % 8)))) {
				buff.r += clr[i + 1][J].r;
				buff.g += clr[i + 1][J].g;
				buff.b += clr[i + 1][J].b;
				++count;
			}
			buff.r /= 5 - count;
			buff.g /= 5 - count;
			buff.b /= 5 - count;
			if (arr[i][j / 8] & (MASK(j % 8))) {
				clr[i][J + 1].r  = _addClr(clr[i][J + 1].r, buff.r);
				clr[i][J + 1].g  = _addClr(clr[i][J + 1].g, buff.g);
				clr[i][J + 1].b  = _addClr(clr[i][J + 1].b, buff.b);
			}  else {
				clr[i][J + 1] = (t_clr){0};
			}
			if (arr[i + 1][j / 8] & (MASK(j % 8))) {
				clr[i + 1][J].r  = _addClr(clr[i + 1][J].r, buff.r);
				clr[i + 1][J].g  = _addClr(clr[i + 1][J].g, buff.g);
				clr[i + 1][J].b  = _addClr(clr[i + 1][J].b, buff.b);
			}  else {
				clr[i + 1][J] = (t_clr){0};
			}
			clr[i][J].r  = _addClr(clr[i][J].r, buff.r);
			clr[i][J].g  = _addClr(clr[i][J].g, buff.g);
			clr[i][J].b  = _addClr(clr[i][J].b, buff.b);
		}
	}
}

__always_inline
void	_negateClr(t_clr *clr) {
	clr->r = 255 - clr->r;
	clr->g = 255 - clr->g;
	clr->b = 255 - clr->b;
}

void	_negative(t_clr *clr[], const uint8_t *arr[], const size_t w, const size_t h) {
	for (size_t i = 0; i < h ; ++i) {
		for (size_t j = 0; j < w; ++j) {
			const size_t	J = j / 2;
			if ((i & 1) == 0) { // even
				if (j & 1) {
					if (!(arr[i][J / 8] & (MASK(J % 8))))
					   _negateClr(&clr[i][j]);
				} 
			} else { //Off
				if ((j & 1) == 0) {
					if (!(arr[i][J / 8] & (MASK(J % 8))))
						_negateClr(&clr[i][j]);
				} else {
					_negateClr(&clr[i][j]);
					printf("%lu %lu\n", j, i);
				}
			}
		}
	}
}

void	applyColorBaseFile(t_art *art) {
	_applyClr_4b4(art->arrClr, (const uint8_t **)art->arr, art->width, 2 * art->height - 1);
	// _negative(art->arrClr, (const uint8_t **)art->arr, art->widthClr, art->heightClr);
}
