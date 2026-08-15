#include "arczn.h"
#include "petri.h"

uint8_t		GPM_Angle(const t_point *point, const t_cluster *cluster) {
	const int64_t	dX = point->x - cluster->xOrigin;	
	const int64_t	dY = point->y - cluster->yOrigin;	

	if (point->distance == 0)
		return (MASK(UP));
	if (!dX && dY < 0)
		return (MASK(UP) | MASK(RIGHT));
	// return (0);
	// return (0b1111);
	uint8_t	mask = 0b1111;
	if (dX > 0 && dY > 0) {
		mask = MASK(DOWN) | MASK(LEFT);
	} else if (dX > 0 && dY < 0) {
		mask = MASK(DOWN) | MASK(RIGHT);
	}else if (dX < 0 && dY > 0) {
		mask = MASK(UP) | MASK(LEFT);
	} else if (dX < 0 && dY < 0){
		mask = MASK(UP) | MASK(RIGHT);
	} else if (dY == 0) {
		mask = MASK(UP) | MASK(DOWN);
	} else if (dX == 0) {
		mask = MASK(RIGHT) | MASK(LEFT);
	}

	if (dX == 0 && dY > 0)
		printf("[%lu , %lu]: %x\n", point->x, point->y, mask);
	return (mask);
}
