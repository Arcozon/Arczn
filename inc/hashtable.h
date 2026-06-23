#ifndef HASHTABLE_H
# define HASHTABLE_H

# include "types.h"
# include <stdlib.h>

typedef struct s_bucket	t_bucket;
typedef struct s_hashTable	t_ht;

struct s_bucket {
	void		*data;
	t_bucket	*next;
};

struct s_hashTable {
	t_bucket	**buckets;
	size_t		nBuckets;
	
	size_t		nItems;

	size_t	(*hashFn)(const void *);

	void	*(*dupFn)(const void *);
	bool	(*cmpFn)(const void *, const void *);
	void	(*freeFn)(void *);
};

t_ht	*ht_create(const size_t,
				size_t (*hashFn)(const void *),
				void *(*dupFn)(const void *),
				bool (*cmpFn)(const void *, const void *),
				void (*freeFn)(void *));
void	ht_destroy(t_ht *ht);

void	*ht_add(t_ht *ht, const void *);
void	*ht_get(t_ht *ht, const void *);
void	ht_rm(t_ht *ht, const void *);

#endif
