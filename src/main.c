#include "arczn.h"

#define DEFAULT_PERCENT	40
#define DEFAULT_TYPE	T_RANDOM
#define DEFAULT_MIN		150
#define DEFAULT_MAX		230
#define DEFAULT_DELTA	7
#define DEFAULT_WIDTH	5
#define DEFAULT_HEIGHT	5
t_nonConstArt	_defaultArt(void) {
	t_nonConstArt	art = {
		.nStart = 1,
		.orphanPercent = 0,
		.percent = DEFAULT_PERCENT,
		.gen = G_RANDOM,
		.fd = STDOUT_FILENO,
		.print = P_COLOR,
		.width = DEFAULT_WIDTH,
		.height = DEFAULT_HEIGHT,
		.arr = NULL,
		.clrSetting = {	.min = DEFAULT_MIN, .max = DEFAULT_MAX,
				.delta = DEFAULT_DELTA, 0, 0},
		.widthClr = 0,
		.heightClr = 0,
		.arrClr = NULL
	};
	return (art);
}

void	freeArt(t_nonConstArt *tab) {
	if (tab->arr != NULL) {
		for (size_t i = 0; tab->arr[i]; ++i)
			free(tab->arr[i]);
		free(tab->arr);
	}
	if (tab->arrClr != NULL) {
		for (size_t i = 0; i < tab->heightClr; ++i)
			free(tab->arrClr[i]);
		free(tab->arrClr);
	}
	if (tab->fd != STDOUT_FILENO)
		close(tab->fd);
}

typedef void	(*genTabFn)(t_art *);
void	selectGenTab(t_art *tab) {
	static const genTabFn _genTabFn[G_MAX] = {
		genTabRandom,	genTabIvy,	genTabPetri
	};
	(*_genTabFn[tab->gen])(tab);
}

typedef void	(*printTabFn)(const int, const t_art *);
void	selectPrintTab(const t_art *tab) {
	static const printTabFn _printTabFn[P_MAX] = {
		printTab,	printNColor,	printFrame
		// printTab,	printTabColor,	printFrame
	};
	(*_printTabFn[tab->print])(tab->fd, tab);
}


int main(int ac, char *av[], char *env[]) {
	__attribute__((cleanup(freeArt)))
	t_nonConstArt	nonConstArt	= _defaultArt();

	if (init(ac, av, &nonConstArt))
		exit(1);
	t_art art = *(t_art*)&nonConstArt;
	selectGenTab(&art);
	selectPrintTab(&art);
	return (0);
	(void)env;
}
