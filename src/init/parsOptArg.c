#include "arczn.h"
#include "parg.h"

void	parsArg_percent(const char *arg, t_nonConstArt *art) {
	art->percent = atoi(arg);
}

void	parsArg_percentOrphan(const char *arg, t_nonConstArt *art) {
	art->orphanPercent = atoi(arg);
}

void	parsArg_width(const char *arg, t_nonConstArt *art) {
	*(size_t *)&art->tab.width = atoi(arg);
}

void	parsArg_height(const char *arg, t_nonConstArt *art) {
	*(size_t *)&art->tab.height = atoi(arg);
}

void	parsArg_nStart(const char *arg, t_nonConstArt *art) {
	art->nStart = atoi(arg);
}

void	parsArg_genRandom(const char *arg, t_nonConstArt *art) {
	art->gen = G_RANDOM;
	(void)arg;
}
void	parsArg_genIvy(const char *arg, t_nonConstArt *art) {
	art->gen = G_IVY;
	(void)arg;
}
void	parsArg_genPetri(const char *arg, t_nonConstArt *art) {
	art->gen = G_PETRI;
	(void)arg;
}

void	parsArg_baseImg(const char *arg, t_nonConstArt *art) {
	art->fNameBase = arg;
	art->color = CLR_BASE_IMG;
}

void	parsArg_FillBg(const char *arg, t_nonConstArt *art) {
	art->fillBg = true;
	(void)arg;
}

void	parsArg_printColor(const char *arg, t_nonConstArt *art) {
	art->color = CLR_GRADIENT;
	(void)arg;
}

void	parsArg_printFrame(const char *arg, t_nonConstArt *art) {
	art->print = P_FRAME;
	(void)arg;
}



void	parsArg_output(const char *arg, t_nonConstArt *art) {
	art->fNameOut = arg;
	art->print = P_PNG;
}
