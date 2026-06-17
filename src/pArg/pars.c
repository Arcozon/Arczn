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

int	parsArg_gen(const char *str) {
	static const struct s_pType	typeList[G_MAX] = {
		{"r", "random", G_RANDOM},
		{"i", "ivy", G_IVY}
	};
	for (size_t i = 0; i < G_MAX; ++i) {
		if (!strcmp(typeList[i].c, str)
			|| !strcmp(typeList[i].str, str))
			return (typeList[i].type);
	}
	return (G_RANDOM);
}

int	parsArg_printColor(const char *str) {
	(void)str;
	return (P_COLOR);
}
