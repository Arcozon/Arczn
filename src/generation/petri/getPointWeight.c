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

	if (cluster->xOrigin > point->x)	dx = -dx;
	if (cluster->yOrigin > point->y)	dy = -dy;
	
	return (dx * dx + dy *dy + 1);
}

uint64_t	GPW_distance_ULDR(const t_point *point, const t_cluster *cluster) {
	size_t dx = cluster->xOrigin - point->x;
	size_t dy = cluster->yOrigin - point->y;

	if (cluster->xOrigin > point->x)	dx = 100 * -dx;
	if (cluster->yOrigin > point->y)	dy = 100 * -dy;
	
	return (dx * dx + dy *dy + 1);
}

uint64_t	GPW_distance_UP(const t_point *point, const t_cluster *cluster) {
	uint64_t	dx = point->x - cluster->xOrigin;
	uint64_t	dy = point->y - cluster->yOrigin;
	
	if (cluster->xOrigin > point->x)	dx = cluster->xOrigin - point->x;
	if (cluster->yOrigin > point->y)	dy = cluster->yOrigin - point->y;
	
	const uint64_t	hipotenus2 = dx * dx + dy * dy;
	const uint64_t	hipotenus = (int)sqrt(hipotenus2);
	const uint64_t	radius = 40;

	if (hipotenus % radius == 0) {
		return (1);
	}
	return (1000);
}


uint64_t	GPW_cut_circle(const t_point *point, const t_cluster *cluster) {
	uint64_t	dx = point->x - cluster->xOrigin;
	uint64_t	dy = point->y - cluster->yOrigin;
	
	if (cluster->xOrigin > point->x)	dx = cluster->xOrigin - point->x;
	if (cluster->yOrigin > point->y)	dy = cluster->yOrigin - point->y;
	
	const uint64_t	hipotenus2 = dx * dx + dy * dy;
	const uint64_t	hipotenus = (int)sqrt(hipotenus2);
	const uint64_t	radius = 50;
	const float	ratio =  (float)19 / 20;

	if (hipotenus % radius == 0) {
		const uint64_t	indexCircle = hipotenus / radius;
		if (indexCircle % 2) {
			if (dy <= hipotenus * ratio)
				return (1);
		} else {
			if (dx <= hipotenus * ratio)
				return (1);
		}
	}
	return (1000000);
}

uint64_t	GPW_circle(const t_point *point, const t_cluster *cluster) {
	uint64_t	dx = point->x - cluster->xOrigin;
	uint64_t	dy = point->y - cluster->yOrigin;
	
	if (cluster->xOrigin > point->x)	dx = cluster->xOrigin - point->x;
	if (cluster->yOrigin > point->y)	dy = cluster->yOrigin - point->y;
	
	const uint64_t	hipotenus2 = dx * dx + dy * dy;
	const uint64_t	hipotenus = (int)sqrt(hipotenus2);

	if (hipotenus == 50) {
		return (1);
	} else if (hipotenus == 165) {
		if (dy < 50000)
			return (1);
		else
			printf("%lu\n", dy);
	}
	return (1000000);
	(void )cluster;
}

uint64_t	GPW_rectangle(const t_point *point, const t_cluster *cluster) {
	const size_t	w = 20;
	const size_t	h = 20;

	if (point->x % w == 0)
		return (10);
	if (point->y % h== 0) 
		return (1);
	return (100);
	(void )cluster;
}
