#include "arczn.h"

void	freeArt(t_art *tab) {
	if (tab->arr != NULL) {
		for (size_t i = 0; tab->arr[i]; ++i)
			free(tab->arr[i]);
		free(tab->arr);
	}
	if (tab->fd != STDOUT_FILENO)
		close(tab->fd);
}

typedef void	(*genTabFn)(t_art *);
void	selectGenTab(t_art *tab) {
	static const genTabFn _genTabFn[G_MAX] = {
		genTabRandom,	genTabIvy
	};
	(*_genTabFn[tab->gen])(tab);
}

typedef void	(*printTabFn)(const int, const t_art);
void	selectPrintTab(t_art *tab) {
	static const printTabFn _printTabFn[P_MAX] = {
		printTab,	printTabColor,	printFrame
	};
	(*_printTabFn[tab->print])(tab->fd, *tab);
}

#define DEFAULT_PERCENT	40
#define DEFAULT_TYPE	T_RANDOM
#define DEFAULT_MIN		150
#define DEFAULT_MAX		230
#define DEFAULT_DELTA	7
#define DEFAULT_WIDTH	5
#define DEFAULT_HEIGHT	5
int main(int ac, char *av[], char *env[]) {
	__attribute__((cleanup(freeArt)))
	t_art	art	= {0, DEFAULT_PERCENT, G_RANDOM,
		STDOUT_FILENO, {DEFAULT_MIN, DEFAULT_MAX, DEFAULT_DELTA, 0, 0}, P_NORMAL,
		DEFAULT_WIDTH, DEFAULT_HEIGHT, NULL};

	if (init(ac, av, &art))
		exit(1);
	
	selectGenTab(&art);
	selectPrintTab(&art);

	return (0);
	(void)ac, (void)av, (void)env;
}
