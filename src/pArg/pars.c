#include "arczn.h"
#include "parg.h"

int	parsArg_output(const char *str) {
	int fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	
	if (fd < 0)
		return (0);
	return (fd);
}

struct s_pType {
	char	*c;
	char	*str;
	e_genType	type;
};

int	parsArg_genRandom(const char *str) {
	(void)str;
	return (G_RANDOM);
}
int	parsArg_genIvy(const char *str) {
	(void)str;
	return (G_IVY);
}
int	parsArg_genPetri(const char *str) {
	(void)str;
	return (G_PETRI);
}

int	parsArg_printColor(const char *str) {
	(void)str;
	return (P_COLOR);
}

int	parsArg_printFrame(const char *str) {
	(void)str;
	return (P_FRAME);
}

int	parsArg_printSavePNG(const char *str) {
	(void)str;
	return (P_PNG);
}
