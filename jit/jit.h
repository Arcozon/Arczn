#ifndef JIT_H
# define JIT_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <time.h>
# include <stdint.h>
# include <stddef.h>
# include <ctype.h>
# include <stdbool.h>


# include <elf.h>
# include <dlfcn.h>

typedef	char *(*generateFileFn_t)(char *fname, const void *settings);

void	*compile(generateFileFn_t generateFileFn, const void *settings);

char	*genTestFile(char *fname, const void *settings);

#endif
