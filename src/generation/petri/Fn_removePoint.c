#include "arczn.h"
#include "petri.h"

//bool	t_removePointFn(const uint8_t choice, const t_point *point, const t_cluster *cluster, const t_bField *bField) {
//	return (false);
//	(void)choice;(void)point;(void)cluster;(void)bField;
//}


bool	RP_test(const uint8_t choice, const t_point *point, const t_cluster *cluster, const t_bField *bField) {
	const int64_t dX = cluster->xOrigin - point->x;
	const int64_t dY = cluster->yOrigin - point->y;
	
	if (!dX && dY > 0)
		return (false);
	return (true);
	(void)choice;(void)point;(void)cluster;(void)bField;
}
