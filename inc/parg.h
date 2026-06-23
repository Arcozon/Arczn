#ifndef PARG_H
# define PARG_H

#include 	"types.h"

enum	e_argType {
	AT_PERCENT = 0,
	AT_ORPHAN_PERCENT,
	AT_WIDTH,
	AT_HEIGHT,
	AT_OUTPUT,
	AT_GENERATION,
	AT_GEN_RANDOM,
	AT_GEN_IVY,
	AT_GEN_PETRI,
	AT_COLOR,
	AT_FRAME,
	AT_CLR_DELTA,
	AT_CLR_MIN,
	AT_CLR_MAX,
	AT_HELP,
	__AT_MAX__
};

struct s_parsArg {
	e_argType	argType;
	size_t		nStrs;
	const char	**strs;
	int		(*fnCheck)(const char *);
	int		(*fnPars)(const char *);
};

int	checkArg_int(const char *);
int	checkArg_output(const char *);
int	checkArg_gen(const char *);


int	parsArg_output(const char *);

int	parsArg_gen(const char *);
int	parsArg_genRandom(const char *);
int	parsArg_genIvy(const char *);
int	parsArg_genPetri(const char *);

int	parsArg_printColor(const char *);
int	parsArg_printFrame(const char *);

#endif
