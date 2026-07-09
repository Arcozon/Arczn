#include "arczn.h"

size_t	genStarts(t_nonConstArt *art) {
	t_startList *starts = malloc(sizeof(starts->n) + sizeof(starts->lStart[0]) * art->nStart);
	if (!starts)
		return (1);
	art->starts = starts;
	starts->n = art->nStart;
	for (size_t i = 0; i < art->nStart; ++i) {
		starts->lStart[i] = (t_start){
			.x = aRand(art->width) * 2,
			.y = aRand(art->height) * 2,
			.baseClr = {0xff,0xff, 0x00},
			.rules = {{0x2f, 0xff, 2}, {0x2f, 0xff, 2}, {0x00, 0x4f, 4}}
		};
	}
	return (0);
}

