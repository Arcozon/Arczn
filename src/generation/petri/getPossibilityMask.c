#include "arczn.h"
#include "petri.h"

uint8_t		getPossibilityMaskFn(const t_point *point, const t_cluster *cluster) {
	(void)point;
	(void)cluster;
	return 0b1111;
}
