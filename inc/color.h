#ifndef COLOR_H
# define COLOR_H

# include <types.h>

struct s_clr {
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
};

t_clr	newColor(const uint8_t min, const uint8_t max)		__attribute__((hot, flatten));
t_clr	seededNewColor(t_clr oldClr, const t_clrSet *set)	__attribute__((hot, flatten));

struct s_oneClrRules {
	uint8_t	max;
	uint8_t	min;
	uint8_t	delta;
};

struct s_clrRules {
	struct s_oneClrRules	r;
	struct s_oneClrRules	g;
	struct s_oneClrRules	b;
};

#endif
