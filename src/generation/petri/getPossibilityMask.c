#include "arczn.h"
#include "petri.h"

uint8_t		GPM_Angle(const t_point *point, const t_cluster *cluster) {
	const int64_t	dX = point->x - cluster->xOrigin;	
	const int64_t	dY = point->y - cluster->yOrigin;	

	if (point->distance == 0)
		return (0b1111);
	if (!dX)
		return (MASK(RIGHT) | MASK(LEFT));
	else if (!dY)
		return (MASK(DOWN) | MASK(UP));
	
	float teta = atan2f(dY, dX);
	uint8_t	mod = ((uint8_t)floorf(((teta) + 2 * M_PI) / (M_PI / 2) )) % NONE;
	
	uint8_t mask = 0b1111;
	if (mod == 0) {
		mask &= ~MASK(UP);
	} else if (mod == 1) {
		mask = 0;
	}else if (mod == 2) {
		mask &= ~MASK(DOWN);
	} else if (mod == 3){
		mask &= ~MASK(LEFT);
	}
	return (mask);
}
