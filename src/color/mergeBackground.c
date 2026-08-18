#include "arczn.h"

typedef struct s_BgPoint	t_BgPoint;
struct s_BgPoint {
	uint64_t	x;
	uint64_t	y;
};

static inline
bool	isInRange(uint64_t x, uint64_t y, uint64_t w, uint64_t h) {
	return (x < w && y < h);
}

static inline
bool	isBg(uint64_t x, uint64_t y, const t_clr *clr[], const t_clr *bgClr) {
	const t_clr	*pClr = &clr[y][x];

	if (pClr->r == bgClr->r
			&& pClr->g == bgClr->g
			&& pClr->b == bgClr->b)
		return (true);
	return (false);
}

static inline
bool	isInRangeBg(uint64_t x, uint64_t y, uint64_t w, uint64_t h, const t_clr *clr[], const t_clr *bgClr) {
	if (!isInRange(x, y, w, h))
		return (false);
	// printf("Chechking %lu:%lu\n", x, y);
	return (isBg(x, y, clr, bgClr));
}


static inline
bool	isBgAndSpreadable(const t_BgPoint *p, const t_clr *clr[], uint64_t w, uint64_t h, const t_clr *bgClr) {
	if (!isBg(p->x, p->y, clr, bgClr))
		return (false);
	if (isInRangeBg(p->x + 1, p->y, w, h, clr, bgClr))	return (true);
	if (isInRangeBg(p->x - 1, p->y, w, h, clr, bgClr))	return (true);
	if (isInRangeBg(p->x, p->y + 1, w, h, clr, bgClr))	return (true);
	if (isInRangeBg(p->x, p->y - 1, w, h, clr, bgClr))	return (true);
	return (false);
}

static inline
uint8_t	gotoNextP(t_BgPoint *p, const uint64_t w, const uint64_t h, uint8_t *dir) {

	if (*dir == DOWN) {
		p->y++;
		if (p->y == h - 1) {
			*dir = (w == 1 ? NONE : RIGHT);
		}
	}
	if (*dir == RIGHT) {
		p->x++;
		if (p->x == w - 1) {
			*dir = (h == 1 ? NONE : UP);
		}
	}
	if (*dir == UP) {
		p->y--;
		if (p->y == 0)
			*dir = LEFT;
	}
	if (*dir == LEFT) {
		p->x--;
		if (p->x == 0)
			*dir = NONE;
	}
	return (*dir);
}

static inline
void	getNextP(t_BgPoint *p, const t_clr *clr[], uint64_t w, uint64_t h, const t_clr *bgClr, uint8_t *dir) {
	do {
		if (gotoNextP(p, w, h, dir) == NONE)
			break;
		if (isBgAndSpreadable(p, clr, w, h, bgClr))
			return ;		
	}	while (true);
}


static inline
t_BgPoint	getFirstP(const t_clr *clr[], uint64_t w, uint64_t h, const t_clr *bgClr, uint8_t *dir) {
	t_BgPoint point = {0, 0};

	if (!isBgAndSpreadable(&point, clr, w, h, bgClr))
		getNextP(&point, clr, w, h, bgClr, dir);
	return (point);
}

uint32_t	checkOneDir(t_vec *vec, const t_BgPoint *p, t_clr *clrArr[], uint64_t w, uint64_t h, const t_clr *bgClr, t_iClr *avrClr) {
	if (!isInRange(p->x, p->y, w, h))
		return (0);
	if (isBg(p->x, p->y, (const t_clr **)clrArr, bgClr)) {
		vec_add(vec, p);
		return (0);
	} else {
		t_clr *clr = &clrArr[p->y][p->x];
		avrClr->r += clr->r;
		avrClr->g += clr->g;
		avrClr->b += clr->b;
		return (1);
	}
}

static inline
void	spreadOnePoint(t_vec *vec, const t_BgPoint *p1, t_clr *clr[], uint64_t w, uint64_t h, const t_clr *bgClr) {
	uint32_t	count;
	t_iClr	avrClr;
	t_BgPoint	p;

	vec_add(vec, p1);
	while (vec->size) {
		count = 0;
		avrClr = (t_iClr){0};
		p = *(const t_BgPoint *)vec_get(vec, vec->size - 1);
		vec_rm(vec, vec->size - 1);

		if (checkOneDir(vec, &(t_BgPoint){.x = p.x + 1, .y = p.y}, clr, w, h, bgClr, &avrClr))	++count;
		if (checkOneDir(vec, &(t_BgPoint){.x = p.x - 1, .y = p.y}, clr, w, h, bgClr, &avrClr))	++count;
		if (checkOneDir(vec, &(t_BgPoint){.x = p.x, .y = p.y + 1}, clr, w, h, bgClr, &avrClr))	++count;
		if (checkOneDir(vec, &(t_BgPoint){.x = p.x, .y = p.y - 1}, clr, w, h, bgClr, &avrClr))	++count;
		if (count == 0)
			return ;
		avrClr.r /= count;
		avrClr.g /= count;
		avrClr.b /= count;
		clr[p.y][p.x].r = avrClr.r;
		clr[p.y][p.x].g = avrClr.g;
		clr[p.y][p.x].b = avrClr.b;
	}
}

void	mergeBackGround(t_clr *clr[], uint64_t w, uint64_t h, const t_clr *bgClr) {
	t_vec		*vPoints = vec_create(sizeof(t_BgPoint));
	uint8_t		dir = h == 1 ? RIGHT : DOWN;
	t_BgPoint	point = getFirstP((const t_clr **)clr, w, h, bgClr, &dir);

	// printf("ClrDim: %lu  %lu\n", w, h);
	do {
		spreadOnePoint(vPoints, &point, clr, w, h, bgClr);
		// printf("[%lu, %lu]\n", point.x, point.y);
		getNextP(&point, (const t_clr **)clr, w, h, bgClr, &dir);
	}	while (dir != NONE);
	vec_destroy(vPoints);
}
