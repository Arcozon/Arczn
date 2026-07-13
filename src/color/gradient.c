#include "arczn.h"
#include "vector.h"

enum e_dir {UP, LEFT, DOWN, RIGHT, NONE};

typedef struct s_petriPoint {
	size_t	x;
	size_t	y;
	enum e_dir	dir;
}	t_petriPoint;

struct s_vecDir{
	int8_t dx;
	int8_t dy;
};


void	_spreadP(enum e_dir dir, const size_t bX, const size_t bY, const t_clr bClr,
		t_clr *arrClr[], const t_clrRules *rules) {
	static const struct s_vecDir	vecDirs[NONE] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
	const struct s_vecDir	vecDir = vecDirs[dir];
	const t_clr	nClr  = seededNewColor_Rules(bClr, rules);

	arrClr[bY + vecDir.dy][bX + vecDir.dx] = nClr;
	arrClr[bY + 2 * vecDir.dy][bX + 2 * vecDir.dx] = seededNewColor_Rules(nClr, rules);
}


__always_inline
void	_checkPSide(const t_art *art, t_vec *vec, const t_petriPoint p, const t_clrRules *rules) {
	const size_t xArr = p.x / 2;
	// printf("Point %lu - %lu: ", p.x, p.y);
	if (p.dir != UP && p.y > 0) {	// Check Up
		// printf(" u?");
		if (art->arr[p.y - 1][xArr / 8] & MASK(xArr % 8)) {
			_spreadP(UP, p.x, p.y, art->arrClr[p.y][p.x], art->arrClr, rules);
			vec_add(vec, &(t_petriPoint){.x = p.x, .y = p.y - 2, .dir = DOWN});
			// printf("U");
		}
	}
	if (p.dir != LEFT && p.x > 0) {	// Check Up
		// printf(" l?");
		const size_t	NxArr = xArr - 1;
		if (art->arr[p.y][NxArr / 8] & MASK(NxArr % 8)) {
			_spreadP(LEFT, p.x, p.y, art->arrClr[p.y][p.x], art->arrClr, rules);
			vec_add(vec, &(t_petriPoint){.x = p.x - 2, .y = p.y, .dir = RIGHT});
			// printf("L");
		}
	}
	if (p.dir != DOWN && p.y + 1 < art->heightClr) {	// Check Up
		// printf(" d?");
		if (art->arr[p.y + 1][xArr / 8] & MASK(xArr % 8)) {
			_spreadP(DOWN, p.x, p.y, art->arrClr[p.y][p.x], art->arrClr, rules);
			vec_add(vec, &(t_petriPoint){.x = p.x, .y = p.y + 2, .dir = UP});
			// printf("D");
		}
	}
	if (p.dir != RIGHT && p.x + 1 < art->widthClr) {	// Check Up
		// printf(" r?");
		if (art->arr[p.y][xArr / 8] & MASK(xArr % 8)) {
			_spreadP(RIGHT, p.x, p.y, art->arrClr[p.y][p.x], art->arrClr, rules);
			vec_add(vec, &(t_petriPoint){.x = p.x + 2, .y = p.y, .dir = LEFT});
			// printf("R");
		}
	}
	// printf("\n");
}


void	applyColorGradient(t_art *art) {
	const t_startList	*starts = art->starts;
	t_vec	*vec = vec_create(sizeof(t_petriPoint));

	for (size_t i = 0; i < starts->n; ++i) {
		const t_clrRules	rules = starts->lStart[i].rules;
		// printf("%lu %lu\n", starts->n, i);
		// printf("%u %u\n", rules.r.min, rules.r.max);
		const t_petriPoint	p_ = {.x = starts->lStart[i].x, .y = starts->lStart[i].y, .dir = NONE};
		
		art->arrClr[p_.y][p_.x] = starts->lStart[i].baseClr;	// Copy First
		vec_add(vec, &p_);
		
		while (vec->size) {
			const t_petriPoint	p = *(t_petriPoint *)vec_get(vec, vec->size - 1);
			vec_rm(vec, vec->size - 1);
			_checkPSide(art, vec, p, &rules);
		}
		// recursive not recusive shit
	}
	vec_destroy(vec);
}
