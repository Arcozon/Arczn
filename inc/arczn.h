#ifndef ARCZN_H
# define ARCZN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>
# include <time.h>

# include <spng.h>

# include "types.h"
# include "color.h"
# include "random.h"
# include "start.h"
# include "petri.h"

# include "debug.h"

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
	P_FRAME,
# define P_FRAME	P_FRAME
	P_PNG,
# define P_PNG	P_PNG
	P_MAX
# define P_MAX		P_MAX
};

enum e_colorType {
	CLR_NONE = 0,
# define CLR_NONE	CLR_NONE
	CLR_GRADIENT,
# define CLR_GRADIENT	CLR_GRADIENT
	CLR_BASE_IMG,
# define CLR_BASE_IMG	CLR_BASE_IMG
	CLR_MAX
# define CLR_MAX		CLR_MAX
};


struct s_tab {
	const size_t	width;
	const size_t	height;
	uint8_t			**arr;
};

struct s_art {
	const uint64_t	nStart;
	const t_startList	*starts;
	// t_startList			*branch;

	const uint8_t	orphanPercent;
	const uint8_t	percent;
	const e_genType	gen;

	t_tab tab;
	
	const uint8_t		fillBg:1;
	const char			*fNameBase;
	const e_colorType	color;

	t_clr			bgColor;
	const size_t	widthClr;
	const size_t	heightClr;
	t_clr			**arrClr;

	const char			*fNameOut;
	const e_printType	print;
};

struct s_nonConstArt {
	uint64_t	nStart;
	t_startList	*starts;

	uint8_t		orphanPercent;
	uint8_t		percent;
	e_genType	gen;
	
	t_tab tab;

	uint8_t		fillBg:1;
	const char	*fNameBase;
	e_colorType	color;
	
	const t_clr	bgColor;
	size_t		widthClr;
	size_t		heightClr;
	t_clr		**arrClr;

	const char	*fNameOut;
	e_printType	print;
};

size_t	init(const int ac, char *av[], t_nonConstArt *art);

uint8_t	genNBit(const uint8_t nBit, const uint8_t percent);
void	genTabRandom(t_art *tab);
void	genTabIvy(t_art *tab);
void	genTabPetri(t_art *tab);

void	applyColorGradient(t_art *art);
void	applyColorBaseFile(t_art *art);

void	mergeBackGround(t_clr *clr[], uint64_t w, uint64_t h, const t_clr *bgClr);

void	printTab(const t_art *tab);
void	printNColor(const t_art *tab);
void	printFrame(const t_art *tab);
void	printSavePng(const t_art *tab);

// DEBUG
void	printPoint(const char strHead[], const t_point *pointCmp);

#endif
 