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
int	checkArg_type(const char *);

int	parsArg_output(const char *);
int	parsArg_typeRandom(const char *str);
int	parsArg_typeIvy(const char *str);
int	parsArg_type(const char *);

#endif
