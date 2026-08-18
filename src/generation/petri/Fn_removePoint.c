#include "arczn.h"
#include "petri.h"

//bool	t_removePointFn(const uint8_t choice, const t_point *point, const t_cluster *cluster, const t_bField *bField) {
//	return (false);
//	(void)choice;(void)point;(void)cluster;(void)bField;
//}


bool	RP_test(const uint8_t choice, const t_point *point, const t_cluster *cluster, const t_bField *bField) {
	const int64_t dX =  point->x - 150;
	const int64_t dY =  point->y - 150;
	const uint64_t	d0 = dY * dY + dX * dX;	
	const uint64_t	r2 = 90 * 90;	
	const uint64_t	delta = 2;	

	if (d0 + delta >= r2)
		return (false);
	return (true);
	(void)choice;(void)point;(void)cluster;(void)bField;
}
