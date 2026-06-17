#include "arczn.h"

typedef char	aChar[sizeof("██") - 1];

#define _FULLACHAR	"██"
#define _MTYACHAR	"  \0\0\0\0"

static const aChar fullAChar __attribute__((nonstring)) = _FULLACHAR;
static const aChar emptyAChar __attribute__((nonstring)) = _MTYACHAR;

void	_printLineEven(const int fdOut, const uint8_t lineTab[], const size_t _width) {
	static const aChar	bLine[]  __attribute__((nonstring)) = {
		"██", "██", "██", "██", "██", "██", "██", "██", "██", "██", "██", "██", "██", "██", "██", "██"};
	aChar line[sizeof(bLine) / sizeof(aChar)]  __attribute__((nonstring)) = {};
	const size_t width = _width - 1;

	for (uint8_t i = 0; i < (width / 8); ++i) {
		memcpy(line, bLine, sizeof(bLine));
		for (uint8_t j = 0; j < 8; ++j) {	
			if (!(lineTab[i] & MASK(j))) {
				memcpy(line + (2 * j + 1), emptyAChar, sizeof(aChar));
			}
		}
		write(fdOut, line, sizeof(line));
		// printf("b\n");
	}
	{
		memcpy(line, bLine, sizeof(bLine));
		for (uint8_t j = 0; j < (width % 8); ++j) {	
			if (!(lineTab[width / 8] & MASK(j))) {
				memcpy(line + (2 * j + 1), emptyAChar, sizeof(aChar));
			}
		}
		write(fdOut, line, sizeof(aChar) * (2 * (width % 8) + 1));
	}
	write(fdOut, "\n", 1);
}

void	_printLineOdd(const int fdOut, const uint8_t lineTab[], const size_t width) {
	static const aChar	bLine[]  __attribute__((nonstring)) = {
		_MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR,
		_MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR
	};
	aChar line[sizeof(bLine) / sizeof(aChar)]  __attribute__((nonstring)) = {};

	for (uint8_t i = 0; i < (width / 8); ++i) {
		memcpy(line, bLine, sizeof(bLine));
		for (uint8_t j = 0; j < 8; ++j) {	
			if ((lineTab[i] & MASK(j))) {
				memcpy(line + (2 * j), fullAChar, sizeof(aChar));
			}
		}
		write(fdOut, line, sizeof(line));
	}
	{
		memcpy(line, bLine, sizeof(bLine));
		for (uint8_t j = 0; j < width % 8; ++j) {	
			if ((lineTab[width / 8] & MASK(j))) {
				memcpy(line + (2 * j), fullAChar, sizeof(aChar));
			}
		}
		write(fdOut, line, sizeof(aChar) * (2 *(width % 8) + 1));
	}
	write(fdOut, "\n", 1);
}

void	printTab(const int fdOut, const t_art tab) {
	(void)fullAChar;
	for (size_t i = 0; tab.arr[i]; ++i) {
		if (i & 1) {
			_printLineOdd(fdOut, tab.arr[i], tab.width);
		} else {
			_printLineEven(fdOut, tab.arr[i], tab.width);
		}
	}
}
