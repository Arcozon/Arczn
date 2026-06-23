#ifndef ARCZN_H
# define ARCZN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>
# include <time.h>

# include "types.h"
# include "color.h"
# include "random.h"

# define MASK(bit)			(1 << (bit))
# define GETB(var, bit)		((var) & MASK(bit))
# define SETB(var, bit)		((var) |= MASK(bit))
# define UNSETB(var, bit)	((var) &= ~MASK(bit))

enum e_genType {
	G_RANDOM = 0,
# define G_RANDOM	G_RANDOM
	G_IVY,
# define G_IVY		G_IVY
	G_MAX
# define G_MAX		G_MAX
};

enum e_printType {
	P_NORMAL = 0,
# define P_NORMAL	P_NORMAL
	P_COLOR,
# define P_COLOR	P_COLOR
	P_FRAME,
# define P_FRAME	P_FRAME
	P_MAX
# define P_MAX		P_MAX
};

struct s_clrSet {
	uint8_t		min;
	uint8_t		max;
	uint8_t		delta;
	uint8_t		spanMinMax;
	uint32_t	spanDelta;
};

struct s_art {
	uint8_t		orphanPercent;
	uint8_t		percent;
	e_genType	gen;
	
	int			fd;
	t_clrSet	clrSetting;
	e_printType	print;

	size_t	width;
	size_t	height;
	uint8_t	**arr;
};

size_t	init(const int ac, char *av[], t_art *art);
void	printTab(const int fdOut, const t_art tab);
void	printTabColor(const int fdOut, const t_art tab);
void	printFrame(const int fdOut, const t_art tab);

uint8_t	genNBit(const uint8_t nBit, const uint8_t percent);
void	genTabRandom(t_art *tab);
void	genTabIvy(t_art *tab);

#endif
