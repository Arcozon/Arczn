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

typedef void	(*fillTabFn)(t_art *);
void	fillTab(t_art *tab) {
	static const fillTabFn _fillTab[G_MAX] = {
		fillTabRandom,	fillTabIvy
	};
	(*_fillTab[tab->gen])(tab);
}

#define DEFAULT_PERCENT	40
#define DEFAULT_TYPE	T_RANDOM
#define DEFAULT_WIDTH	5
#define DEFAULT_HEIGHT	5
int main(int ac, char *av[], char *env[]) {
	__attribute__((cleanup(freeArt)))
	t_art	art	= {STDOUT_FILENO, G_RANDOM, DEFAULT_PERCENT,
		DEFAULT_WIDTH, DEFAULT_HEIGHT, NULL};

	srand(time(NULL));
	if (init(ac, av, &art))
		exit(1);
	
	fillTab(&art);

	printTab(art.fd, art);
	return (0);
	(void)ac, (void)av, (void)env;
}
