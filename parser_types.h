#ifndef PARSER_TYPES_H
# define PARSER_TYPES_H

#include "types.h"
#include "arczn.h"
#include "color.h"

#include <string.h>

typedef struct s_parsConfig {
	uint64_t	width;
	uint64_t	height;
	char		*fName;
	
	uint64_t	nStart;
	t_start		*starts;

	// defaultClr
	// default clrBound

	uint64_t	width_Defined:1;
	uint64_t	height_Defined:1;
	uint64_t	fName_Defined:1;
	uint64_t	nStart_Defined:1;
}	t_parsConfig;

typedef struct s_parsStart {
	t_start	start;

	uint64_t	x_Defined:1;
	uint64_t	y_Defined:1;
	uint64_t	clr_Defined:1;
	uint64_t	rules_Defined:1;
	uint64_t	weight_Defined:1;
	// function
}	t_parsStart;

typedef struct s_parsClr {
	t_clr	clr;

	uint64_t	r_Defined:1;
	uint64_t	g_Defined:1;
	uint64_t	b_Defined:1;
}	t_parsClr;

typedef struct s_parsClrRules {
	t_clrRules	rules;

	uint64_t	r_Defined:1;
	uint64_t	g_Defined:1;
	uint64_t	b_Defined:1;
}	t_parsClrRules;

typedef struct s_oneClrRule {
	t_oneClrRules	rules;

	uint64_t	min_Defined:1;
	uint64_t	max_Defined:1;
	uint64_t	delta_Defined:1;
}	t_oneClrRule;

#endif
