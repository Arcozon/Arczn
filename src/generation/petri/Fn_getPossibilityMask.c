#include "arczn.h"
#include "petri.h"

uint8_t		GPM_Angle(const t_point *point, const t_cluster *cluster) {
	const int64_t	dX = point->x - 150;	
	const int64_t	dY = point->y - 150;	
	
	const uint64_t	d0 = dY * dY + dX * dX;	
	const uint64_t	r2 = 90 * 90;	

	if (d0 < r2)
	{
		uint8_t mask = 0b0000;
		if (dX >= 0) {
			mask |= MASK(RIGHT);
		}
		if (dX <= 0) {
			mask |= MASK(LEFT);
		}
		if (dY >= 0) {
			mask |= MASK(DOWN);
		}
		if (dY <= 0) {
			mask |= MASK(UP);
		}
		return (mask);
	}
	return (0b1111);
	(void)cluster;
}
