#include "arczn.h"

# define MAX_RAND_DATA	512

typedef struct s_randData	T_randData;
struct s_randData {
	int		fdRand;
	uint64_t	i;
	uint64_t	random[MAX_RAND_DATA];
	uint64_t	precision;
};

static T_randData	randData = {0, MAX_RAND_DATA, {0}, 0};

__attribute__((constructor))
void	_openFdRand(void) {
	const char	fdRandom[] = "/dev/urandom";
	randData.fdRand = open(fdRandom, O_RDONLY);
	if (randData.fdRand < 0) {
		fprintf(stderr, "Error: cannot open random file `%s'\n", fdRandom);
		exit(1);
	}
}

__attribute__((destructor))
void	_closeFdRand(void) {
	close(randData.fdRand);
}

__attribute__((always_inline, hot))
static inline uint64_t	_getRand(const uint64_t range) {
	if (!range)
		return (0);
	if (randData.precision <= range) {
		++randData.i;
		if (randData.i >= MAX_RAND_DATA) {
			// fprintf(stderr,"read\n");
			read(randData.fdRand, randData.random, sizeof(randData.random));
			randData.i = 0;
		}
		randData.precision = (uint64_t)-1;
	}
	const uint64_t	res = randData.random[randData.i] % range;
	randData.random[randData.i] /= range;
	randData.precision /= range + range;
	return (res);
}
__attribute__((hot, alias("_getRand")))
uint64_t	aRand(const uint64_t range);

__attribute__((hot))
uint64_t	aRandRange(const uint64_t min, const uint64_t max) {
	return (min + _getRand(max - min + 1));
}

uint8_t	genNBit(const uint8_t nBit, const uint8_t percent) {
	uint8_t	res = 0;

	for (uint8_t i = 0; i < nBit; ++i) {
		if (_getRand(100) < percent)
			res |= MASK(i);
	}
	return (res);
}
