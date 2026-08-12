#include "arczn.h"
#include "petri.h"

uint8_t		GPM_Angle(const t_point *point, const t_cluster *cluster) {
	const int64_t	dX = point->x - cluster->xOrigin;	
	const int64_t	dY = point->y - cluster->yOrigin;	

	float teta = 0;
	if (point->distance != 0)
		teta = atan2f(dY, dX);
	// uint8_t	mod = ((uint8_t)floorf(((teta + 2 * M_PI / 3) + 2 * M_PI) / (M_PI / 2) )) % NONE;
	uint8_t	mod = ((uint8_t)floorf(((teta + M_PI / 4) + 2 * M_PI) / (M_PI / 2) )) % NONE;
	
	uint8_t mask = 0b1111;
	if (mod == 0 && dX != 0) {
		mask &= ~MASK(UP);
	} else if (mod == 1 && dY != 0) {
		mask &= ~MASK(RIGHT);
	}else if (mod == 2 && dX != 0) {
		mask &= ~MASK(DOWN);
	} else if (mod == 3 && dY != 0){
		mask &= ~MASK(LEFT);
	}
	return (mask);
}
