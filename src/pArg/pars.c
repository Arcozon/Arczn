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
	e_artType	type;
};

int	parsArg_typeRandom(const char *str) {
	(void)str;
	return (T_RANDOM);
}
int	parsArg_typeIvy(const char *str) {
	(void)str;
	return (T_IVY);
}

int	parsArg_type(const char *str) {
	static const struct s_pType	typeList[T_MAX] = {
		{"r", "random", T_RANDOM},
		{"i", "ivy", T_IVY}
	};
	for (size_t i = 0; i < T_MAX; ++i) {
		if (!strcmp(typeList[i].c, str)
			|| !strcmp(typeList[i].str, str))
			return (typeList[i].type);
	}
	return (T_RANDOM);
}
