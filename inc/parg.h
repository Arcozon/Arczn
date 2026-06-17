#ifndef PARG_H
# define PARG_H

#include <ctype.h>

struct s_parsArg {
	char	c;
	char	*str;
	int		(*fnCheck)(const char *);
	int		(*fnPars)(const char *);
};

int	checkArg_int(const char *);
int	checkArg_output(const char *);
int	checkArg_gen(const char *);

int	parsArg_output(const char *);
int	parsArg_genRandom(const char *str);
int	parsArg_genIvy(const char *str);
int	parsArg_gen(const char *);

#endif
