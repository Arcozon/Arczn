#include "arczn.h"

__always_inline
void	_print2Char(const int fdOut, const t_clr *fg, const t_clr *bg) {
	static const char	format[] = "\033[38;2;%d;%d;%dm██\033[48;2;%d;%d;%dm  ";

	dprintf(fdOut, format, fg->r, fg->g, fg->b, bg->r, bg->g, bg->b);
}

void	printNColor(const int fdOut, const t_art *tab) {
	for (size_t i = 0; i < tab->heightClr; ++i) {
		const t_clr	*line = tab->arrClr[i];	
		for (size_t j = 0; j + 2 < tab->widthClr; j += 2) {
			_print2Char(fdOut, &line[j], &line[j + 1]);
		}
		const t_clr	last = line[tab->widthClr - 1];	
		dprintf(fdOut, "\033[48;2;%d;%d;%dm  \n", last.r, last.g, last.b);
	}
}
