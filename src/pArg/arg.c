#include "arczn.h"
#include "parg.h"

uint8_t	**allocArray(const size_t width, const size_t height) {
	uint8_t	**arr = NULL;

	arr = calloc(2 * height, sizeof(uint8_t *));
	if (!arr)	return (arr);

	const size_t	wOver8 = ((width + 7) / 8);
	
	for (size_t i = 0; i < height * 2 - 1; ++i) {
		arr[i] = calloc(wOver8, sizeof(uint8_t));
		if (!arr[i]) {
			for (size_t j = 0; j < i; ++j)
				free(arr[j]);
			free(arr);
			return (NULL);
		}
	}
	return (arr);
}

static const char	*_strsPercent[] = {"-p", "--percent"};
static const char	*_strsOrphan[] = {"-O", "--orphan"};
static const char	*_strsNStart[] = {"-s", "--start"};
static const char	*_strsWidth[] = {"-w", "--width"};
static const char	*_strsHeight[] = {"-h", "--height"}	;
static const char	*_strsOutput[] = {"-o", "--output"};
static const char	*_strsGenRandom[] = {"--random"};
static const char	*_strsGenIvy[] = {"--ivy"};
static const char	*_strsGenPetri[] = {"--petri"};
static const char	*_strsColor[] = {"-c", "--color"};
static const char	*_strsFrame[] = {"--frame"};
static const char	*_strsClrDelta[] = {"-d", "--delta"};
static const char	*_strsClrMin[] = {"-m", "--min"};
static const char	*_strsClrMax[] = {"-M", "--max"};
static const char	*_strsHelp[] =	{"--help"} ;

static const t_parsArg	pArg[__AT_MAX__] = {
		[AT_PERCENT] = {.optType = AT_PERCENT, .fnCheck = checkArg_int, .fnPars  = parsArg_percent,
			.nStrs = sizeof(_strsPercent) / sizeof(char *), .strs  = _strsPercent},
		[AT_ORPHAN_PERCENT] = {.optType = AT_ORPHAN_PERCENT, .fnCheck = checkArg_int, .fnPars  = parsArg_percentOrphan,
			.nStrs = sizeof(_strsOrphan) / sizeof(char *), .strs  = _strsOrphan},
		[AT_NUM_START] = {.optType = AT_NUM_START, .fnCheck = checkArg_int_NotZero, .fnPars  = parsArg_nStart,
			.nStrs = sizeof(_strsNStart) / sizeof(char *), .strs  = _strsNStart},
		[AT_WIDTH] = {.optType = AT_WIDTH, .fnCheck = checkArg_int_NotZero, .fnPars  = parsArg_width,
			.nStrs = sizeof(_strsWidth) / sizeof(char *), .strs  = _strsWidth},
		[AT_HEIGHT] = {.optType = AT_HEIGHT, .fnCheck = checkArg_int_NotZero, .fnPars  = parsArg_height,
			.nStrs = sizeof(_strsHeight) / sizeof(char *), .strs  = _strsHeight},
		[AT_GEN_RANDOM] = {.optType = AT_GEN_RANDOM, .fnCheck = NULL, .fnPars  = parsArg_genRandom,
			.nStrs = sizeof(_strsGenRandom) / sizeof(char *), .strs  = _strsGenRandom},
		[AT_GEN_IVY] = {.optType = AT_GEN_IVY, .fnCheck = NULL, .fnPars  = parsArg_genIvy,
			.nStrs = sizeof(_strsGenIvy) / sizeof(char *), .strs  = _strsGenIvy},
		[AT_GEN_PETRI] = {.optType = AT_GEN_PETRI, .fnCheck = NULL, .fnPars  = parsArg_genPetri,
			.nStrs = sizeof(_strsGenPetri) / sizeof(char *), .strs  = _strsGenPetri},
		[AT_COLOR] = {.optType = AT_COLOR, .fnCheck = NULL, .fnPars  = parsArg_printColor,
			.nStrs = sizeof(_strsColor) / sizeof(char *), .strs  = _strsColor},
		[AT_OUTPUT] = {.optType = AT_OUTPUT, .fnCheck = checkArg_output, .fnPars  = parsArg_output,
			.nStrs = sizeof(_strsOutput) / sizeof(char *), .strs  = _strsOutput},
		[AT_FRAME] = {.optType = AT_FRAME, .fnCheck = NULL, .fnPars  = parsArg_printFrame,
			.nStrs = sizeof(_strsFrame) / sizeof(char *), .strs  = _strsFrame},
		[AT_CLR_DELTA] = {.optType = AT_CLR_DELTA, .fnCheck = checkArg_int, .fnPars  = parsArg_clrDelta,
			.nStrs = sizeof(_strsClrDelta) / sizeof(char *), .strs  = _strsClrDelta},
		[AT_CLR_MIN] = {.optType = AT_CLR_MIN, .fnCheck = checkArg_int, .fnPars  = parsArg_clrMin,
			.nStrs = sizeof(_strsClrMin) / sizeof(char *), .strs  = _strsClrMin},
		[AT_CLR_MAX] = {.optType = AT_CLR_MAX, .fnCheck = checkArg_int, .fnPars  = parsArg_clrMax,
			.nStrs = sizeof(_strsClrMax) / sizeof(char *), .strs  = _strsClrMax},
		[AT_HELP] = {.optType = AT_HELP, .fnCheck = NULL, .fnPars  = NULL,
			.nStrs = sizeof(_strsHelp) / sizeof(char *), .strs  = _strsHelp},
	};
	
e_optType	_getOptType(char *av[], const int argN, const char **toPars) {
	const char	*arg = av[argN];
	size_t	i = 0;
	size_t	j = 0;

	*toPars = av[argN + 1];
	for (i = 0; i < __AT_MAX__; ++i) {
		for (j = 0; j < pArg[i].nStrs; ++j) {
			const char	*toCmp = pArg[i].strs[j];
			if (!strncmp(toCmp, "--", 2)) {	// If starts with '--'
				if (!strcmp(toCmp, arg)) {
					*toPars = av[argN + 1];
					printf("Found large opt `%s`\n", *toPars);
					return (i);
				}
			} else {	// Starts with -
				if (!strncmp(toCmp, arg, strlen(toCmp))) {
					if (arg[strlen(toCmp)])
						*toPars = &arg[strlen(toCmp)];
					return (i);
				}
			}
		}
	}
	return (__AT_MAX__);
}

struct s_arg	_getArgVal(char *av[], const int argN) {
	struct s_arg	res = { .err = PERR_NONE, .optType = __AT_MAX__,
			.parsArg = NULL, .optArgument = av[argN + 1]};
	
	res.optType = _getOptType(av, argN, &res.optArgument);
	// printf("Opt: %u | [%s]\n", res.optType, res.optArgument);
	// printf("`%s` | `%s` \n", av[argN], res.optArgument);
	if (res.optType == __AT_MAX__) {
		res.err = PERR_UNKNOWN_OPT;
	} else {
		res.parsArg = &pArg[res.optType];
		if (!res.parsArg->fnCheck) {
			res.optArgument = NULL;
		} else if (res.parsArg->fnCheck(res.optArgument)){
			res.err = PERR_INVALID_ARG;
		}
	}
	return (res);
}

size_t	_parsArg(const int ac, char *av[], t_nonConstArt *art) {
	for (int i = 1; i < ac; ++i) {
		const struct s_arg	arg = _getArgVal(av, i);
		if (arg.err == PERR_UNKNOWN_OPT || arg.parsArg == NULL) {
			fprintf(stderr, "%s: Unknown option `%s'\n", av[0], av[i]);
			return (1);
		} else if (arg.err == PERR_INVALID_ARG) {
			fprintf(stderr, "%s: Invalid argument to option %s: `%s'\n", av[0], av[i], arg.optArgument);
			return (1);
		}
		if (arg.parsArg->fnPars)
			arg.parsArg->fnPars(arg.optArgument, art);
		if (arg.optArgument && (arg.optArgument < av[i] || arg.optArgument > av[i] + strlen(av[i]))) {
			printf("Skip\n");
			++i;
		}
		else
			printf("Dont Skip\n");
		printf("`%s` | `%s` \n", av[i], arg.optArgument);
	}
	return (0);
}

void	_fillSettings(t_clrSet *set) {
	if (set->max < set->min)
		set->max = set->min;
	set->spanMinMax = set->max - set->min + 1;
	if (set->delta > set->spanMinMax)
		set->delta = set->spanMinMax;
	set->spanDelta = set->delta * 2 + 1;
}

size_t	_check(const t_nonConstArt *art) {
	if (art->width == 0)	return (1);
	else if (art->height == 0)	return (1);
	return (0);
}

size_t	_allocClr(t_nonConstArt *art) {
	*(size_t *)&(art->widthClr) = art->width * 2 - 1;
	*(size_t *)&(art->heightClr) = art->height * 2 - 1;
	art->arrClr = calloc(art->heightClr, sizeof(art->arrClr[0]));
	if (!art->arrClr)	return (1);
	for (size_t i = 0; i < art->heightClr; ++i) {
		art->arrClr[i] = calloc(art->widthClr, sizeof(art->arrClr[0][0]));
		if (!art->arrClr[i])
			return (1);
	}
	return (0);
}

size_t	init(const int ac, char *av[], t_nonConstArt *art) {
	if (_parsArg(ac, av, art))
		return (1);
	if (_check(art))
		return (1);
	_fillSettings((t_clrSet *)&art->clrSetting);
	art->arr = allocArray(art->width, art->height);
	if (!art->arr)
		return (1);
	if (_allocClr(art))
		return (1);
	return (0);
}
