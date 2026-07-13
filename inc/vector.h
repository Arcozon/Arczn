#ifndef VECTOR_H
# define VECTOR_H

# include <stdlib.h>
# include <string.h>

# include "types.h"

#define VECTOR_DEFAULT_SIZE	(128)

typedef struct s_vector	t_vec;
struct s_vector	{
	size_t	size;
	void	*arr;
	
	const size_t	sizeOfType;
	size_t	capacity;
};

t_vec	*vec_create(const size_t);
void	vec_destroy(t_vec *);
void	*vec_add(t_vec *, const void *val);
void	vec_rm(t_vec *, const size_t);
void	*vec_get(t_vec *vec, const size_t index);

#endif
