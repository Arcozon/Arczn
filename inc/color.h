#ifndef COLOR_H
# define COLOR_H

# include <types.h>

struct s_clr {
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
};


t_clr	newColor(const uint8_t min, const uint8_t max)		__attribute__((hot));
t_clr	seededNewColor(t_clr oldClr, const t_clrSet set)	__attribute__((hot));

#endif
