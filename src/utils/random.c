#include "arczn.h"

# define MAX_RAND_DATA	512
typedef struct s_randData	T_randData;
struct s_randData {
	int		fdRand;
	size_t	i;
	size_t	random[MAX_RAND_DATA];
	size_t	precision;
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
static inline size_t	_getRand(const size_t range) {
	if (!range)
		return (0);
	if (randData.precision <= range) {
		++randData.i;
		if (randData.i >= MAX_RAND_DATA) {
			// fprintf(stderr,"read\n");
			read(randData.fdRand, randData.random, sizeof(randData.random));
			randData.i = 0;
		}
		randData.precision = (size_t)-1;
	}
	const size_t	res = randData.random[randData.i] % range;
	randData.random[randData.i] /= range;
	randData.precision /= range + range;
	return (res);
}

__attribute__((hot))
size_t	aRand(const size_t range) {
	return (_getRand(range));
}

__attribute__((hot))
size_t	aRandRange(const size_t min, const size_t max) {
	return (min + _getRand(max - min + 1));
}
