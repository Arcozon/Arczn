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
static const char	*_strsWidth[] = {"-w", "--width"};
static const char	*_strsHeight[] = {"-h", "--height"}	;
static const char	*_strsOutput[] = {"-o", "--output"};
static const char	*_strsGeneration[] = {"-g", "--gen", "--generation"};
static const char	*_strsGenRandom[] = {"--random"};
static const char	*_strsGenIvy[] = {"--ivy"};
static const char	*_strsGenPetri[] = {"--petri"};
static const char	*_strsColor[] = {"-c", "--color"};
static const char	*_strsFrame[] = {"--frame"};
static const char	*_strsClrDelta[] = {"-d", "--delta"};
static const char	*_strsClrMin[] = {"-m", "--min"};
static const char	*_strsClrMax[] = {"-M", "--max"};
static const char	*_strsHelp[] =	{"--help"} ;

const t_parsArg	*_getArgVal(const char str[], const char *pStr[], const char *nxt) {
	static const t_parsArg	pArg[__AT_MAX__] = {
		[AT_PERCENT] = {.argType = AT_PERCENT, .fnCheck = checkArg_int, .fnPars  = atoi,
			.nStrs = sizeof(_strsPercent) / sizeof(char *), .strs  = _strsPercent},
		[AT_ORPHAN_PERCENT] = {.argType = AT_ORPHAN_PERCENT, .fnCheck = checkArg_int, .fnPars  = atoi,
			.nStrs = sizeof(_strsOrphan) / sizeof(char *), .strs  = _strsOrphan},
		[AT_WIDTH] = {.argType = AT_WIDTH, .fnCheck = checkArg_int, .fnPars  = atoi,
			.nStrs = sizeof(_strsWidth) / sizeof(char *), .strs  = _strsWidth},
		[AT_HEIGHT] = {.argType = AT_HEIGHT, .fnCheck = checkArg_int, .fnPars  = atoi,
			.nStrs = sizeof(_strsHeight) / sizeof(char *), .strs  = _strsHeight},
		[AT_OUTPUT] = {.argType = AT_OUTPUT, .fnCheck = checkArg_output, .fnPars  = parsArg_output,
			.nStrs = sizeof(_strsOutput) / sizeof(char *), .strs  = _strsOutput},
		[AT_GENERATION] = {.argType = AT_GENERATION, .fnCheck = checkArg_gen, .fnPars  = parsArg_gen,
			.nStrs = sizeof(_strsGeneration) / sizeof(char *), .strs  = _strsGeneration},
		[AT_GEN_RANDOM] = {.argType = AT_GEN_RANDOM, .fnCheck = NULL, .fnPars  = parsArg_genRandom,
			.nStrs = sizeof(_strsGenRandom) / sizeof(char *), .strs  = _strsGenRandom},
		[AT_GEN_IVY] = {.argType = AT_GEN_IVY, .fnCheck = NULL, .fnPars  = parsArg_genIvy,
			.nStrs = sizeof(_strsGenIvy) / sizeof(char *), .strs  = _strsGenIvy},
		[AT_GEN_PETRI] = {.argType = AT_GEN_PETRI, .fnCheck = NULL, .fnPars  = parsArg_genPetri,
			.nStrs = sizeof(_strsGenPetri) / sizeof(char *), .strs  = _strsGenPetri},
		[AT_COLOR] = {.argType = AT_COLOR, .fnCheck = NULL, .fnPars  = parsArg_printColor,
			.nStrs = sizeof(_strsColor) / sizeof(char *), .strs  = _strsColor},
		[AT_FRAME] = {.argType = AT_FRAME, .fnCheck = NULL, .fnPars  = parsArg_printFrame,
			.nStrs = sizeof(_strsFrame) / sizeof(char *), .strs  = _strsFrame},
		[AT_CLR_DELTA] = {.argType = AT_CLR_DELTA, .fnCheck = checkArg_int, .fnPars  = atoi,
			.nStrs = sizeof(_strsClrDelta) / sizeof(char *), .strs  = _strsClrDelta},
		[AT_CLR_MIN] = {.argType = AT_CLR_MIN, .fnCheck = checkArg_int, .fnPars  = atoi,
			.nStrs = sizeof(_strsClrMin) / sizeof(char *), .strs  = _strsClrMin},
		[AT_CLR_MAX] = {.argType = AT_CLR_MAX, .fnCheck = checkArg_int, .fnPars  = atoi,
			.nStrs = sizeof(_strsClrMax) / sizeof(char *), .strs  = _strsClrMax},
		[AT_HELP] = {.argType = AT_HELP, .fnCheck = NULL, .fnPars  = NULL,
			.nStrs = sizeof(_strsHelp) / sizeof(char *), .strs  = _strsHelp},
	};
	size_t	i = 0;
	size_t	j = 0;

	*pStr = NULL;
	for (i = 0; i < __AT_MAX__; ++i) {
		for (j = 0; j < pArg[i].nStrs; ++j) {
			const char	*toCmp = pArg[i].strs[j];
			if (!strncmp(toCmp, "--", 2)) {	// If starts with '--'
				if (!strcmp(toCmp, str)) {
					break ;
				}
			} else {	// Starts with -
				if (!strncmp(toCmp, str, strlen(toCmp))) {
					if (str[strlen(toCmp)])
						*pStr = &str[strlen(toCmp)];
					break ;
				}
			}
		}
		if (j != pArg[i].nStrs)	// Found Match
			break ;
	}
	if (i == __AT_MAX__)
		return (NULL);
	if (pArg[i].fnCheck) {
		if (!*pStr)
			*pStr = nxt;
		if (!*pStr || pArg[i].fnCheck(*pStr))
			return (NULL);
	}
	return (&pArg[i]);
}

size_t	_parsArg(const int ac, char *av[], t_nonConstArt *art) {
	const char	*optVal = NULL;
	const struct s_parsArg	*arg = NULL;

	for (int i = 1; i < ac; ++i) {
		arg = _getArgVal(av[i], &optVal, av[i + 1]);
		if (!arg) {
			fprintf(stderr, "Unknown opt `%s'\n", av[i]);
			return (1);
		}
		if (optVal == av[i + 1]) {
			++i;
		}

		switch (arg->argType) {
			case AT_PERCENT:	art->percent = arg->fnPars(optVal);
				break;
			case AT_ORPHAN_PERCENT:	art->orphanPercent = arg->fnPars(optVal);
				break;
			case AT_WIDTH:	art->width = arg->fnPars(optVal);
				break;
			case AT_HEIGHT:	art->height = arg->fnPars(optVal);
				break;
			case AT_OUTPUT:	art->fd = arg->fnPars(optVal);
				break;
			case AT_GENERATION:
			case AT_GEN_IVY:
			case AT_GEN_PETRI:	art->gen = arg->fnPars(optVal);
				break;
			case AT_COLOR:
			case AT_FRAME:		art->print = arg->fnPars(optVal);
				break;
			case AT_CLR_DELTA:	art->clrSetting.delta = arg->fnPars(optVal);
				break;
			case AT_CLR_MIN:	art->clrSetting.min = arg->fnPars(optVal);
				break;
			case AT_CLR_MAX:	art->clrSetting.max = arg->fnPars(optVal);
				break;
			default:	fprintf(stderr, "Unknown opt `%s'\n", av[i]);
				return (1);
		}
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
	// printf("%u-%u (%u) | %u (%u)\n", set->max, set->min, set->spanMinMax, set->delta, set->spanDelta);
}

size_t	_check(const t_nonConstArt *art) {
	if (art->fd < 0)			return (1);
	else if (art->width == 0)	return (1);
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
