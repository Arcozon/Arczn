#include "arczn.h"

#define _FULLACHAR	"██"
#define _MTYACHAR	"  \0\0\0\0"

typedef char	aChar[sizeof("██") - 1];
static const aChar fullAChar __attribute__((nonstring)) = _FULLACHAR;
static const aChar emptyAChar __attribute__((nonstring)) = _MTYACHAR;

static const aChar	fullLine[]  __attribute__((nonstring)) = {
		"██", "██", "██", "██", "██", "██", "██", "██", "██", "██", "██", "██", "██", "██", "██", "██"};
static const aChar	emptyLine[]  __attribute__((nonstring)) = {
		_MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR,
		_MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR, _MTYACHAR
	};

static const aChar	leftBorder[2]  __attribute__((nonstring)) = {_FULLACHAR, _MTYACHAR};
static const aChar	rightBorder[2]  __attribute__((nonstring)) = {_MTYACHAR, _FULLACHAR};

static void	_printLineEven(const int fdOut, const uint8_t lineTab[], const size_t _width) {
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
}

static void	_printLineOdd(const int fdOut, const uint8_t lineTab[], const size_t width) {
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
		write(fdOut, line, sizeof(aChar) * (2 *(width % 8) - 1));
	}
}

static void	_printN(const int fdOut, const size_t n, const aChar patern[]) {
	for (size_t i = 0; i < (n / (sizeof(fullLine) / sizeof(fullLine[0]))); ++i)
		write(fdOut, patern, sizeof(fullLine));
	write(fdOut, patern, sizeof(aChar) * (n % (sizeof(fullLine) / sizeof(fullLine[0]))));
}

void	printFrame(const int fdOut, const t_art *tab) {
	const size_t trueWidth = tab->width * 2 - 1;
	_printN(fdOut, trueWidth + 4, fullLine);
	write(fdOut, "\n", 1);
	write(fdOut, leftBorder, sizeof(leftBorder));
	_printN(fdOut, trueWidth, emptyLine);
	write(fdOut, rightBorder, sizeof(rightBorder));
	write(fdOut, "\n", 1);
	for (size_t i = 0; tab->arr[i]; ++i) {
		write(fdOut, leftBorder, sizeof(leftBorder));
		if (i & 1) {
			_printLineOdd(fdOut, tab->arr[i], tab->width);
		} else {
			_printLineEven(fdOut, tab->arr[i], tab->width);
		}
		write(fdOut, rightBorder, sizeof(rightBorder));
		write(fdOut, "\n", 1);
	}
	write(fdOut, leftBorder, sizeof(leftBorder));
	_printN(fdOut, trueWidth, emptyLine);
	write(fdOut, rightBorder, sizeof(rightBorder));
	write(fdOut, "\n", 1);
	_printN(fdOut, trueWidth + 4, fullLine);
	write(fdOut, "\n", 1);
}
