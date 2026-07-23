#include "arczn.h"
#include "vector.h"

enum e_dir {UP, LEFT, DOWN, RIGHT, NONE};

typedef struct s_point {
	size_t	x;
	size_t	y;
	enum e_dir	dirOrig;
	const t_clr	*clrOrig;
}	t_point;

struct s_vecDir {
	int8_t dx;
	int8_t dy;
};

static const struct s_vecDir	vecDirs[NONE] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

__always_inline __attribute__((const)) static
uint8_t	isFilled(const uint8_t *arr[], uint64_t w, uint64_t h, uint64_t xClr, uint64_t y, enum e_dir direction) {
	uint64_t	x = xClr / 2;	// HERE

	if (direction == UP) {
		if (y > 0) {
			return (arr[y - 1][x / 8] & MASK(x % 8));
		} else
			return (0);
	} else if (direction == DOWN) {
		if (y + 1 < h) {
			return (arr[y + 1][x / 8] & MASK(x % 8));
		} else
			return (0);
	} else if (direction == LEFT) {
		if (x > 0) {
			uint64_t	nX = x - 1;
			return (arr[y][nX / 8] & MASK(nX % 8));
		} else
			return (0);
	} else if (direction == RIGHT) {
		if (x + 1 < w) {
			return (arr[y][x / 8] & MASK(x % 8));
		} else
			return (0);
	}
	return (0);
}

__always_inline static
void	checkAllPossibleDir(const uint8_t *arr[], uint64_t w, uint64_t h, const t_point *origin, t_vec *vecPts) {
	const enum e_dir	dir = origin->dirOrig;
	const size_t		X = origin->x;
	const size_t		Y = origin->y;

	if (dir != LEFT && dir != RIGHT) {	// Add Left Right
		if (isFilled(arr, w, h, X, Y, LEFT)) {
			vec_add(vecPts, &(t_point){.x = X - 2, .y = Y, .dirOrig = LEFT, .clrOrig = origin->clrOrig});
		}
		if (isFilled(arr, w, h, X, Y, RIGHT)) {
			vec_add(vecPts, &(t_point){.x = X + 2, .y = Y, .dirOrig = RIGHT, .clrOrig = origin->clrOrig});
		}
	}
	if (dir != UP && dir != DOWN) {
		if (isFilled(arr, w, h, X, Y, UP)) {
			vec_add(vecPts, &(t_point){.x = X, .y = Y - 2, .dirOrig = UP, .clrOrig = origin->clrOrig});
		}
		if (isFilled(arr, w, h, X, Y, DOWN)) {
			vec_add(vecPts, &(t_point){.x = X, .y = Y + 2, .dirOrig = DOWN, .clrOrig = origin->clrOrig});
		}
	}
}

__always_inline static
void	_spreadClrOnDir(const t_point *p, const struct s_vecDir dir, t_clr *arrClr[], const t_clrRules *rules) {
	const uint64_t	bX = p->x;
	const uint64_t	bY = p->y;

	newSeededNewColor_Rules_2(&arrClr[bY - dir.dy][bX - dir.dx], &arrClr[bY][bX], p->clrOrig, rules);
}

__always_inline static
void	_FillLine(const t_art *art, t_vec *vecPts, t_point p, const t_clrRules *rules) {
	const struct s_vecDir	vecDir = vecDirs[p.dirOrig];

	do {
		_spreadClrOnDir(&p, vecDir, art->arrClr, rules);
		p.clrOrig =  &art->arrClr[p.y][p.x];
		checkAllPossibleDir((const uint8_t **)art->arr, art->width, art->heightClr, &p, vecPts);
		if (!isFilled((const uint8_t **)art->arr, art->width, art->heightClr, p.x, p.y, p.dirOrig))
			break ;
		p.x += 2 * vecDir.dx;
		p.y += 2 * vecDir.dy;
	} while (1);
}


__attribute__((flatten))
void	applyColorGradient(t_art *art) {
	const t_startList	*starts = art->starts;
	t_vec	*vec = vec_create(sizeof(t_point));

	for (size_t i = 0; i < starts->n; ++i) {
		const t_clrRules	rules = starts->lStart[i].rules;
		const t_point	pStart = {.x = starts->lStart[i].x, .y = starts->lStart[i].y,
								.dirOrig = NONE, .clrOrig = &art->arrClr[pStart.y][pStart.x]};
		
		art->arrClr[pStart.y][pStart.x] = starts->lStart[i].baseClr;	// Copy First
		checkAllPossibleDir((const uint8_t **)art->arr, art->width, art->heightClr, &pStart, vec);
		while (vec->size) {
			const t_point	p = *(t_point *)vec_get(vec, vec->size - 1);
			vec_rm(vec, vec->size - 1);
			_FillLine(art, vec, p, &rules);
		}
	}
	vec_destroy(vec);
}
