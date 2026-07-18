#include "arczn.h"
#include "petri.h"

uint64_t	GPW_One(const t_point *point, const t_cluster *cluster) {
	return (1);
	(void)point;
	(void)cluster;
}

uint64_t	GPW_distance(const t_point *point, const t_cluster *cluster) {
	size_t dx = cluster->xOrigin - point->x;
	size_t dy = cluster->yOrigin - point->y;

	if (cluster->xOrigin < point->x)	dx = -dx;
	if (cluster->yOrigin < point->y)	dy = -dy;
	
	return (3 * dx + dy + 1);
}
