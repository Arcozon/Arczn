#include "arczn.h"
#include "petri.h"

uint8_t	CPD_random(const uint8_t poss, const t_point *point, const t_cluster *cluster) {	
	uint8_t	r = aRand(__builtin_popcount(poss));
	uint8_t	i;

	for (i = 0; i < NONE; ++i) {
		if (poss & MASK(i)) {
			if (!r) {
				return (i);
			}
			--r;
		}
	}
	return (i);
	(void)point;(void)cluster;
}

uint8_t	CPD_binary(const uint8_t poss, const t_point *point, const t_cluster *cluster) {
	static uint8_t	choice[NONE] = {UP, DOWN, LEFT, RIGHT};
	// const int64_t	dX = point->x - cluster->xOrigin;	
	// const int64_t	dY = point->y - cluster->yOrigin;	

	uint8_t d = 0;
	if ((point->x / 2) & 1) {
		d = 2;
	}
	uint8_t i = 0;
	for (i = 0; i < NONE; ++i) {
		if (poss & MASK(choice[(i + d) % NONE])) {
				return (choice[(i + d) % NONE]);
		}
	}
	return (1);
	(void)poss;(void)point;(void)cluster;
}

uint8_t	CPD_angle(const uint8_t poss, const t_point *point, const t_cluster *cluster) {
	const int64_t	dX = point->x - cluster->xOrigin;	
	const int64_t	dY = point->y - cluster->yOrigin;	

	float teta = 0;
	if (point->distance != 0)
		teta = atan2f(dY, dX);
	// teta += M_PI / 4;
	float chanceXf = cos(teta);
	float chanceYf = sin(teta);
	uint8_t	mChoiceX = MASK(chanceXf > 0 ? LEFT : RIGHT);
	uint8_t	mChoiceY = MASK(chanceYf > 0 ? UP : DOWN);

	if (poss & (mChoiceX | mChoiceY)) {
		if ((poss & (mChoiceX | mChoiceY)) == (mChoiceX | mChoiceY)) {
			uint64_t	chanceX = (uint64_t)roundf(fabs(chanceXf * 10000));
			uint64_t	chanceY = (uint64_t)roundf(fabs(chanceYf * 10000));
			if (aRand(chanceX + chanceY) < chanceX)
				return (__builtin_ctz(mChoiceX));
			else
				return (__builtin_ctz(mChoiceX));
		} else {
			return (__builtin_ctz(poss & (mChoiceX | mChoiceY)));
		}
	} else {
		return (__builtin_ctz(poss));
	}
	return (1);
	(void)poss;(void)point;(void)cluster;
}

uint8_t	CPD_angle_save(const uint8_t poss, const t_point *point, const t_cluster *cluster) {
	static uint8_t	choice[NONE] = {UP, LEFT, DOWN, RIGHT};
	const int64_t	dX = point->x - cluster->xOrigin;	
	const int64_t	dY = point->y - cluster->yOrigin;	

	float teta = 0;
	if (point->distance != 0)
		teta = atan2f(dY, dX);
	uint8_t	mod = ((uint8_t)floorf(teta / (M_PI / 2) )) % NONE;
	uint8_t	i = 0;
	for (i = 0; i < NONE; ++i) {
		if (poss & MASK(choice[(i + mod) % NONE])) {
				return (choice[(i + mod) % NONE]);
		}
	}
	return (1);
	(void)poss;(void)point;(void)cluster;
}

uint8_t	CPD_first(const uint8_t poss, const t_point *point, const t_cluster *cluster) {
	return (__builtin_ctz(poss));
	(void)poss;(void)point;(void)cluster;
}

# define MK_CPD_ORDER(name, c1, c2, c3, c4) \
uint8_t	CPD_##name(const uint8_t poss, const t_point *point, const t_cluster *cluster) {	\
	if (poss & MASK(c1))		return (c1);	\
	else if (poss & MASK(c2))	return (c2);	\
	else if (poss & MASK(c3))	return (c3);	\
	else 						return (c4);	\
	(void)point;(void)cluster;\
}

MK_CPD_ORDER(ULRD, UP, LEFT, RIGHT, DOWN)
MK_CPD_ORDER(ULDR, UP, LEFT, DOWN, RIGHT)
