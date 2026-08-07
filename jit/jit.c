#include "jit.h"

# define BUFFER_SIZE 512

static struct {
	void	*sArr[2];
	void	**arr;
	size_t	n;
	size_t	cap;
}	ClHandles = {.arr = ClHandles.sArr, .n = 0, .cap = BUFFER_SIZE};

__attribute__((destructor))
static void	_free_ClHandles(void) {
	for (size_t i = 0; i < ClHandles.n; ++i) {
		dlclose(ClHandles.arr[i]);
	}
	if (ClHandles.arr != ClHandles.sArr)
		free(ClHandles.arr);
}

static void	_pushDlHanble(void *handle) {
	if (ClHandles.n == ClHandles.cap) {
		size_t	newCapacity = ClHandles.cap + ClHandles.cap / 2;
		if (ClHandles.arr == ClHandles.sArr) {
			ClHandles.arr = calloc(newCapacity, sizeof(void *));
			memcpy(ClHandles.arr, ClHandles.sArr, sizeof(ClHandles.sArr));
		} else {
			ClHandles.arr = realloc(ClHandles.arr, newCapacity * sizeof(void *));
		}
		ClHandles.cap = newCapacity;
	}
	ClHandles.arr[ClHandles.n] = handle;
	++ClHandles.n;
}

void	getFOut(char fOut[BUFFER_SIZE], const char *file) {
	if (strrchr(file, '/')  != NULL)
		file = strrchr(file, '/') + 1;
	snprintf(fOut, BUFFER_SIZE, "/tmp/%s", file);
	char	*pLaseDot = strrchr(fOut, '.');
	if (pLaseDot == NULL) {
		strncat(fOut, ".so", BUFFER_SIZE);
	} else {
		strncpy(pLaseDot, ".so", pLaseDot - fOut + BUFFER_SIZE);
	}
	// printf("Fout = '%s'\n", fOut);
}

void	*compile(generateFileFn_t generateFileFn, const void *settings) {
	char	fInBuffer[BUFFER_SIZE];
	char	*fIn = generateFileFn(fInBuffer, settings);
	char	fOut[BUFFER_SIZE];
	char	bufferCmd[2 * BUFFER_SIZE];

	if (!fIn)
		return (NULL);
	getFOut(fOut, fIn);
	snprintf(bufferCmd, sizeof(bufferCmd), "cc -shared -fPIC -xc -o%s %s", fOut, fIn);
	// printf("cmd = '%s'\n", bufferCmd);

	// printf("Compiled\n");
	if (system(bufferCmd))
		return (NULL);
	void *handle = dlopen(fOut, RTLD_NOW);
	if (!handle)
		return (NULL);
	_pushDlHanble(handle);
	return (dlsym(handle, "function"));
}

char	*genTestFile(char *fname, const void *vSettings) {
	const char	*settings = vSettings;
	snprintf(fname, BUFFER_SIZE, "/tmp/Test%d.c", (int)*settings);

	if (access(fname, F_OK)) {
		FILE	*file = fopen(fname, "w+");
		fprintf(file, "#include <stdio.h>\nvoid function(void) {printf(\"%c\\n\");}", *settings);
		fclose(file);
	} else {
		printf("existed\n");
	}
	return (fname);
}
