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

typedef enum e_artType	e_artType;
enum e_artType {
	T_RANDOM = 0,
# define T_RANDOM	T_RANDOM
	T_IVY,
# define T_IVY		T_IVY
	T_MAX
# define T_MAX		T_MAX
};

typedef struct s_art	t_art;
struct s_art {
	int		fd;
	
	e_artType	type;
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
