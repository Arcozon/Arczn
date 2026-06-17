#ifndef ARCZN_H
# define ARCZN_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <fcntl.h>
# include <time.h>

# define MASK(bit)			(1 << (bit))
# define GETB(var, bit)		((var) & MASK(bit))
# define SETB(var, bit)		((var) |= MASK(bit))
# define UNSETB(var, bit)	((var) &= ~MASK(bit))

typedef enum e_genType	e_genType;
enum e_genType {
	G_RANDOM = 0,
# define G_RANDOM	G_RANDOM
	G_IVY,
# define G_IVY		G_IVY
	G_MAX
# define G_MAX		G_MAX
};

typedef enum e_printType	e_printType;
enum e_printType {
	P_NORMAL = 0,
# define P_NORMAL	P_NORMAL
	P_COLOR,
# define P_COLOR	P_COLOR
	P_MAX
# define P_MAX		P_MAX
};


typedef struct s_art	t_art;
struct s_art {
	int		fd;
	
	e_genType	gen;
	uint8_t		percent;

	size_t	width;
	size_t	height;
	uint8_t	**arr;
};

size_t	init(const int ac, char *av[], t_art *art);
void	printTab(const size_t fdOut, const t_art tab);

uint8_t	genNBit(const uint8_t nBit, const uint8_t percent);
void	fillTabRandom(t_art *tab);
void	fillTabIvy(t_art *tab);


#endif
