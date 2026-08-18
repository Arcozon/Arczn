#include "arczn.h"
#include "petri.h"

__attribute__((const))
uint64_t	dist2Num(uint64_t a, uint64_t b) {
	if (a > b)
		return (a - b);
	return (b - a);
}

uint8_t	CPD_Test(const uint8_t poss, const uint8_t possMask, const t_point *point, const t_cluster *cluster) {
	const uint64_t distCenter = 90 * 90;

	const int64_t	dX = point->x - 150;
	const int64_t	dY = point->y - 150;
	
	uint8_t choice = NONE;
	uint8_t bestChoice = choice;
	uint64_t bestDist = 505;
	do {
		choice--;
		if (!(poss & MASK(choice)))
			continue;
		int64_t	nX = dX;
		int64_t	nY = dY;
		if (choice == UP)	--nY;
		if (choice == DOWN)	++nY;
		if (choice == LEFT)	--nX;
		if (choice == RIGHT)++nX;
		uint64_t nDist = dist2Num(distCenter, nY * nY + nX * nX);
		if (nDist < bestDist) {
			bestChoice = choice;
			bestDist = nDist;
		}
	} while (choice != 0);
	if (bestChoice == NONE)
		return CPD_random(poss, possMask, point, cluster);
	return (bestChoice);
	(void)poss;(void)point;(void)cluster;(void)possMask;
}


uint8_t	CPD_random(const uint8_t poss, const uint8_t possMask, const t_point *point, const t_cluster *cluster) {	
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
	(void)point;(void)cluster;(void)possMask;
}

uint8_t	CPD_binary(const uint8_t poss, const uint8_t possMask, const t_point *point, const t_cluster *cluster) {
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
	(void)poss;(void)point;(void)cluster;(void)possMask;
}

uint8_t	CPD_angle(const uint8_t poss, const uint8_t possMask, const t_point *point, const t_cluster *cluster) {
	const int64_t	dX = point->x - cluster->xOrigin;	
	const int64_t	dY = point->y - cluster->yOrigin;	

	float teta = 0;
	if (point->distance != 0)
		teta = atan2f(dY, dX);
	float chanceXf = cos(teta);
	float chanceYf = sin(teta);
	uint8_t	mChoiceX = MASK(chanceXf < 0 ? LEFT : RIGHT);
	uint8_t	mChoiceY = MASK(chanceYf > 0 ? UP : DOWN);
	printf("[%lu , %lu]: \n", point->x, point->y);
	if (dY == 0 && dX > 0)
		printf("[%lu , %lu]: \n", point->x, point->y);
	if (poss & (mChoiceX | mChoiceY)) {		// TODOL -> This no work
		if ((poss & (mChoiceX | mChoiceY)) == (mChoiceX | mChoiceY)) {
			uint64_t	chanceX = (uint64_t)roundf(fabs(chanceXf * 1000000));
			uint64_t	chanceY = (uint64_t)roundf(fabs(chanceYf * 1000000));
			
			if (aRand(chanceX + chanceY) < chanceX)
				return (__builtin_ctz(mChoiceX));
			else
				return (__builtin_ctz(mChoiceY));
		} else {
			return (__builtin_ctz(poss & (mChoiceX | mChoiceY)));
		}
	} else {
		return (__builtin_ctz(poss));
	}
	(void)poss;(void)point;(void)cluster;(void)possMask;
}

uint8_t	CPD_angle_save(const uint8_t poss, const uint8_t possMask, const t_point *point, const t_cluster *cluster) {
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
	(void)poss;(void)point;(void)cluster;(void)possMask;
}

uint8_t	CPD_first(const uint8_t poss, const uint8_t possMask, const t_point *point, const t_cluster *cluster) {
	return (__builtin_ctz(poss));
	(void)poss;(void)point;(void)cluster;(void)possMask;
}

# define MK_CPD_ORDER(name, c1, c2, c3, c4) \
uint8_t	CPD_##name(const uint8_t poss, const uint8_t possMask, const t_point *point, const t_cluster *cluster) {	\
	if (poss & MASK(c1))		return (c1);	\
	else if (poss & MASK(c2))	return (c2);	\
	else if (poss & MASK(c3))	return (c3);	\
	else 						return (c4);	\
	(void)point;(void)cluster;(void)possMask;\
}

MK_CPD_ORDER(ULRD, UP, LEFT, RIGHT, DOWN)
MK_CPD_ORDER(ULDR, UP, LEFT, DOWN, RIGHT)
