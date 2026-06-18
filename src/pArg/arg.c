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

const struct s_parsArg	*_getArgVal(const char str[], const char *pStr[], const char *nxt) {
	static const struct s_parsArg	pArg[] = {
			{'p', "-percent", checkArg_int, atoi},
			{'w', "-width", checkArg_int, atoi},
			{'h', "-height", checkArg_int, atoi},
			{'o', "-output", checkArg_output, parsArg_output},
			{'g', "-gen", checkArg_gen, parsArg_gen},
			{'g', "-random", NULL, parsArg_genRandom},
			{'g', "-ivy", NULL, parsArg_genIvy},
			{'c', "-color", NULL, parsArg_printColor},
			{'h', "-help", NULL, NULL},
	};
	const size_t nArg = (sizeof(pArg) / sizeof(pArg[0]));
	size_t	i = 0;

	*pStr = NULL;
	if (str[0] != '-')
		return (NULL);
	for (i = 0; i < nArg; ++i) {
		if (!strcmp(&str[1], pArg[i].str)) {
			break ;
		} else if (str[1] == pArg[i].c) {
			if (str[2]) {
				*pStr = &str[2];
			}
			break ;
		}
	}
	if (i == nArg)
		return (NULL);
	if (pArg[i].fnCheck) {
		if (!*pStr)
			*pStr = nxt;
		if (!*pStr || pArg[i].fnCheck(*pStr))
			return (NULL);

	}
	return (&pArg[i]);
}

size_t	_parsArg(const int ac, char *av[], t_art *art) {
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

		switch (arg->c) {
			case 'p':	art->percent = arg->fnPars(optVal);
				break;
			case 'w':	art->width = arg->fnPars(optVal);
				break;
			case 'h':	art->height = arg->fnPars(optVal);
				break;
			case 'o':	art->fd = arg->fnPars(optVal);
				break;
			case 'g':	art->gen = arg->fnPars(optVal);
				break;
			case 'c':	art->print = arg->fnPars(optVal);
				break;
			default:	fprintf(stderr, "Unknown opt `%s'\n", av[i]);
				return (1);
		}
	}
	return (0);
}

void	_fillSettings(t_clrSet *set) {
	set->spanMinMax = set->max - set->min;
	set->spanDelta = set->delta * 2 + 1;
}

size_t	_check(t_art *art) {
	if (art->fd < 0)
		return (1);
	else if (art->width == 0)
		return (1);
	else if (art->height == 0)
		return (1);
	return (0);
}

size_t	init(const int ac, char *av[], t_art *art) {
	if (_parsArg(ac, av, art))
		return (1);
	if (_check(art))
		return (1);
	_fillSettings(&art->clrSetting);
	art->arr = allocArray(art->width, art->height);
	if (!art->arr)
		return (1);
	return (0);
}
