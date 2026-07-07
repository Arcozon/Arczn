#ifndef ARCZN_H
# define ARCZN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>
# include <time.h>

# include "spng.h"

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
	G_PETRI,
# define G_PETRI	G_PETRI
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
	P_PNG,
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
	const uint64_t	nStart;
	const uint8_t	orphanPercent;
	const uint8_t	percent;
	const e_genType	gen;
	
	const char			*fName;
	const e_printType	print;
	
	const size_t	width;
	const size_t	height;
	uint8_t	**arr;
	
	const t_clrSet		clrSetting;
	const size_t	widthClr;
	const size_t	heightClr;
	t_clr	**arrClr;
};

struct s_nonConstArt {
	uint64_t	nStart;
	uint8_t		orphanPercent;
	uint8_t		percent;
	e_genType	gen;
	
	const char		*fName;
	e_printType	print;
	
	size_t	width;
	size_t	height;
	uint8_t	**arr;
	
	t_clrSet	clrSetting;
	size_t	widthClr;
	size_t	heightClr;
	t_clr	**arrClr;
};

size_t	init(const int ac, char *av[], t_nonConstArt *art);

uint8_t	genNBit(const uint8_t nBit, const uint8_t percent);
void	genTabRandom(t_art *tab);
void	genTabIvy(t_art *tab);
void	genTabPetri(t_art *tab);

void	printTab(const t_art *tab);
void	printNColor(const t_art *tab);
void	printFrame(const t_art *tab);
void	printSavePng(const t_art *tab);

#endif
 