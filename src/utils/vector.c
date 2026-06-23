#include "vector.h"
#include <stdio.h>

t_vec	*vec_create(const size_t sizeOfType) {
	t_vec	*vec = malloc(sizeof(*vec));

	if (vec == NULL) {
		return (NULL);
	}
	*(size_t *)&vec->sizeOfType = sizeOfType;
	vec->size = 0;
	vec->capacity = VECTOR_DEFAULT_SIZE;
	vec->arr = malloc(sizeOfType * VECTOR_DEFAULT_SIZE);
	if (!vec->arr) {
		free(vec);
		return (NULL);
	}
	return (vec);
};

void	vec_destroy(t_vec *vec) {
	free(vec->arr);
	free(vec);
}

void	*vec_add(t_vec *vec, const void *val) {
	if (vec->size >= vec->capacity) {
		vec->capacity *= 2;
		vec->arr = realloc(vec->arr, vec->capacity);
		if (!vec->arr)
			return (NULL);
	}
	memcpy(vec->arr + (vec->size * vec->sizeOfType), val, vec->sizeOfType);
	++vec->size;
	return (vec->arr);
}

void	vec_rm(t_vec *vec, const size_t index) {
	if (index >= vec->size) {
		fprintf(stderr, "Vector error: Index out of bound\n");
		return ;
	}
	if (index + 1 != vec->size) {
		memcpy(vec->arr + (index * vec->sizeOfType), vec->arr + ((vec->size - 1) * vec->sizeOfType), vec->sizeOfType);
	}
	--vec->size;
}
