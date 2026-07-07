#ifndef PARG_H
# define PARG_H

#include 	"types.h"

enum	e_optType {
	AT_PERCENT = 0,
	AT_ORPHAN_PERCENT,
	AT_NUM_START,
	AT_WIDTH,
	AT_HEIGHT,
	AT_GEN_RANDOM,
	AT_GEN_IVY,
	AT_GEN_PETRI,
	AT_FRAME,
	AT_OUTPUT,
	AT_BASE_IMG,
	AT_COLOR,
	AT_CLR_DELTA,
	AT_CLR_MIN,
	AT_CLR_MAX,
	AT_HELP,
	__AT_MAX__
};

enum e_parsErr {
	PERR_NONE,
	PERR_UNKNOWN_OPT,
	PERR_INVALID_ARG,
	PERR_MAX
};

struct s_parsArg {
	e_optType	optType;
	size_t		nStrs;
	const char	**strs;
	int		(*fnCheck)(const char *);
	void	(*fnPars)(const char *, t_nonConstArt *);
};

struct s_arg {
	enum e_parsErr		err;
	e_optType			optType;
	const struct s_parsArg	*parsArg;
	const char			*optArgument;
};

size_t	_allocClr(t_nonConstArt *art);

int	checkArg_int(const char *);
int	checkArg_int_NotZero(const char *);
int	checkArg_output(const char *);
int	checkArg_gen(const char *);

int	checkArg_baseImg(const char *);

void	parsArg_percent(const char *, t_nonConstArt *);
void	parsArg_percentOrphan(const char *, t_nonConstArt *);
void	parsArg_nStart(const char *, t_nonConstArt *);
void	parsArg_width(const char *, t_nonConstArt *);
void	parsArg_height(const char *, t_nonConstArt *);

void	parsArg_clrMin(const char *, t_nonConstArt *);
void	parsArg_clrMax(const char *, t_nonConstArt *);
void	parsArg_clrDelta(const char *, t_nonConstArt *);

void	parsArg_genRandom(const char *, t_nonConstArt *);
void	parsArg_genIvy(const char *, t_nonConstArt *);
void	parsArg_genPetri(const char *, t_nonConstArt *);

void	parsArg_baseImg(const char *, t_nonConstArt *);
void	parsArg_printColor(const char *, t_nonConstArt *);

void	parsArg_printFrame(const char *, t_nonConstArt *);
void	parsArg_output(const char *, t_nonConstArt *);

int	parsBaseImage(const char *baseFName, t_nonConstArt *art);

#endif
