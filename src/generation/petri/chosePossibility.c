#include "arczn.h"
#include "petri.h"

uint8_t	CPF_random(const uint8_t poss) {	
	uint8_t	r = aRand(__builtin_popcount(poss));
	uint8_t	i;

	for (i = 0; i < 4; ++i) {
		if (poss & MASK(i)) {
			if (!r) {
				return (i);
			}
			--r;
		}
	}
	return (i);
}

uint8_t	CPF_first(const uint8_t poss) {
	return (__builtin_ctz(poss));
}

# define MK_CPF_ORDER(name, c1, c2, c3, c4) \
uint8_t	CPF_##name(const uint8_t poss) {	\
	if (poss & MASK(c1))		return (c1);	\
	else if (poss & MASK(c2))	return (c2);	\
	else if (poss & MASK(c3))	return (c3);	\
	else 						return (c4);	\
}

MK_CPF_ORDER(ULRD, UP, LEFT, RIGHT, DOWN)
