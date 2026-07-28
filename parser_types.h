#ifndef PARSER_TYPES_H
# define PARSER_TYPES_H

#include "types.h"
#include "arczn.h"
#include "color.h"

typedef struct s_parsStart {
	uint64_t	x;
	uint64_t	y;

	t_clr		clr;
	t_clrRules	rules;
	
	uint64_t	weight;

	uint64_t	x_Defined:1;
	uint64_t	y_Defined:1;
	uint64_t	clr_Defined:1;
	uint64_t	rules_Defined:1;
	uint64_t	weight_Defined:1;
}	t_parsStart;

#endif
