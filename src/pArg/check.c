#include "arczn.h"
#include "parg.h"

int	checkArg_int(const char *str) {
	for (size_t i = 0; str[i]; ++i) {
		if (!isdigit(str[i]))
			return (1);
	}
	return (0);
}

int	checkArg_output(const char *) {
	return (0);
}

int	checkArg_type(const char *str) {
	static const char	*typeList[T_MAX * 2] = {
		"random", "r",
		"ivy", "i"
	};
	for (size_t i = 0; i < T_MAX * 2; ++i) {
		if (!strcmp(typeList[i], str))
			return (0);
	}
	return (1);
}
