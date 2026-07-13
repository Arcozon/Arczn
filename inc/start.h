#ifndef START_H
# define START_H

#include "types.h"

struct s_start {
	size_t	x;
	size_t	y;
	size_t	weight;

	t_clr		baseClr;
	t_clrRules	rules;
};

struct s_startList {
	size_t	n;
	t_start	lStart[];
};

size_t	genStarts(t_nonConstArt *art);


#endif
