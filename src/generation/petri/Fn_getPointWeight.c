#include "arczn.h"
#include "petri.h"

uint64_t	GPW_One(const t_point *point, const t_cluster *cluster) {
	return (1);
	(void)point;
	(void)cluster;
}

uint64_t	GPW_distance(const t_point *point, const t_cluster *cluster) {
	uint64_t dx = cluster->xOrigin - point->x;
	uint64_t dy = cluster->yOrigin - point->y;

	if (cluster->xOrigin > point->x)	dx = -dx;
	if (cluster->yOrigin > point->y)	dy = -dy;
	
	return (dx * dx + dy *dy + 1);
}

uint64_t	GPW_distance_ULDR(const t_point *point, const t_cluster *cluster) {
	uint64_t dx = cluster->xOrigin - point->x;
	uint64_t dy = cluster->yOrigin - point->y;

	if (cluster->xOrigin > point->x)	dx = 100 * -dx;
	if (cluster->yOrigin > point->y)	dy = 100 * -dy;
	
	return (dx * dx + dy *dy + 1);
}

uint64_t	GPW_test(const t_point *point, const t_cluster *cluster) {
	const int64_t	dX = point->x - cluster->xOrigin;	
	const int64_t	dY = point->y - cluster->yOrigin;	

	if (point->distance == 0)
		return (1);
	if (!dX && dY < 0)
		return (1000000);
	return (point->distance);
	return (dX * dX + dY * dY);
}

uint64_t	GPW_spiral2(const t_point *point, const t_cluster *cluster) {
	const float	radius = 70;
	const float	baseTeta = 120;
	const float d0 = 0.15;

	int64_t	dx = point->x - cluster->xOrigin;
	int64_t	dy = point->y - cluster->yOrigin;
	
	if (point->distance == 0)
		return (1);
	const uint64_t	hipotenus2 = dx * dx + dy * dy;
	const float	hipotenus = sqrt(hipotenus2);
	const float teta0 = atan2f(dy, dx);
	const float teta = (hipotenus - baseTeta) / radius - teta0;
	const float k = fabs(teta) / (2 * M_PI);
	const float kMod1 = k - (int)k;
	if (kMod1 > 1 - d0 || kMod1 < d0) {
		return (1000);
	}
	return (0);
}

uint64_t	GPW_spiral(const t_point *point, const t_cluster *cluster) {
	const float	radius = 1.5;
	const float	baseTeta = M_PI;
	const float d0 = 0.18;

	int64_t	dx = point->x - cluster->xOrigin;
	int64_t	dy = point->y - cluster->yOrigin;
	
	if (point->distance == 0)
		return (1);
	const uint64_t	hipotenus2 = dx * dx + dy * dy;
	const float	hipotenus = sqrt(hipotenus2);
	const float teta0 = atan2f(dy, dx);
	const float teta = (hipotenus - baseTeta) / radius - teta0;
	const float k = fabs(teta) / (2 * M_PI);
	const float kMod1 = k - (int)k;
	if (kMod1 > 1 - d0 || kMod1 < d0) {
		return (0);
	}
	return (1);
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
	const uint64_t	radius = 8;

	if (hipotenus % radius == 0) {
		return (1);
	}
	return (1000);
}

uint64_t	GPW_rectangle(const t_point *point, const t_cluster *cluster) {
	const uint64_t	w = 20;
	const uint64_t	h = 20;

	if (point->x % w == 0)
		return (10);
	if (point->y % h== 0) 
		return (1);
	return (100);
	(void )cluster;
}
