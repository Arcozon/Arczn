#ifndef COLOR_H
# define COLOR_H

# include <types.h>

struct s_iClr {
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
};

struct s_clr {
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
};

t_clr	newColor(const uint8_t min, const uint8_t max)		__attribute__((hot, flatten));
t_clr	seededNewColor(t_clr oldClr, const t_clrSet *set)	__attribute__((hot, flatten));

struct s_oneClrRules {
	uint8_t	min;
	uint8_t	max;
	uint8_t	delta;
};

struct s_clrRules {
	t_oneClrRules	r;
	t_oneClrRules	g;
	t_oneClrRules	b;
};

t_clr	seededNewColor_Rules(t_clr oldCLr, const t_clrRules * restrict rules)	__attribute__((hot, flatten));
void	newSeededNewColor_Rules(t_clr *restrict pClr,const t_clr *restrict oldCLr, const t_clrRules * restrict rules)	__attribute__((hot, flatten));
void	newSeededNewColor_Rules_2(t_clr *restrict pClr1, t_clr *restrict pClr2, const t_clr *restrict oldCLr, const t_clrRules * restrict rules)	__attribute__((hot, flatten));

#endif
