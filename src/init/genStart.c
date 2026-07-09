#include "arczn.h"

size_t	genStarts(t_nonConstArt *art) {
	t_startList *starts = malloc(sizeof(starts->n) + sizeof(starts->lStart[0]) * art->nStart);
	if (!starts)
		return (1);
	art->starts = starts;
	starts->n = art->nStart;
	// printf("%lu - %lu\n", art->width, art->height);
	// printf("%lu - %lu\n", art->width * 2 - 1, art->height * 2 - 1);
	for (size_t i = 0; i < art->nStart; ++i) {
		starts->lStart[i] = (t_start){
			.x = aRand(art->width) * 2,
			.y = aRand(art->height) * 2,
			.baseClr = {0x46,0xb2, 0x3c},
			// .baseClr = {0xef,0xff, 0xf0},
			// .rules = {{0x2f, 0xef, 1}, {0x2f, 0xff, 15}, {0x00, 0xf0, 1}}
			// .rules = (t_clrRules){{0x00, 0x3f, 6}, {0x70, 0xff, aRand(6)}, {0x00, 0x3f, 2}}
			// .rules = (t_clrRules){{0x00, 0x3f, 6}, {0x70, 0xff, 1}, {0x00, 0x3f, 2}}
			.rules = {{0x56, 0x8f, 6}, {0x69, 0x92, 1}, {0x3c, 0x5e, 1}}
			// .rules = {{0x2f, 0xff, 2}, {0x2f, 0xff, 2}, {0x00, 0x4f, 4}}
		};
		// printf("Start %lu: [%lu : %lu]\n", i, starts->lStart[i].x, starts->lStart[i].y);
	}
	if (art->nStart > 1)
		starts->lStart[1].rules = (t_clrRules){{0x9f, 0xff, 10}, {0x69, 0x92, 1}, {0x3c, 0x5e, 1}};
	starts->lStart[0].rules = (t_clrRules){{0x9f, 0xff, 1}, {0x69, 0x92, 1}, {0x3c, 0x5e, 1}};
	for (size_t i = 0; i < art->nStart; ++i) {
		t_clrRules rules = starts->lStart[i].rules;
		printf("%lu: %u %u\n", i, rules.r.min, rules.r.max);
	}
	
	return (0);
}

// #AF69EE
// #46923c
