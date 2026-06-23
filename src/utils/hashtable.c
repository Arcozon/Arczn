#include "hashtable.h"

t_ht	*ht_create(const size_t size,
		size_t (*hashFn)(const void *),
		void	*(*dupFn)(const void *),
		bool (*cmpFn)(const void *, const void *),
		void (*freeFn)(void *)) {
	t_ht *res = malloc(sizeof(*res));

	if (res == NULL)
		return (NULL);
	res->buckets = calloc(size, sizeof(res->buckets[0]));
	if (res->buckets == NULL) {
		free(res);
		return (NULL);
	}
	res->nBuckets = size;
	res->nItems = 0;
	res->hashFn = hashFn;

	res->dupFn = dupFn;
	res->cmpFn = cmpFn;
	res->freeFn = freeFn;
	return (res);
}

void	ht_destroy(t_ht *ht) {
	for (size_t i = 0; i < ht->nBuckets; ++i) {
		t_bucket	*item = ht->buckets[i];
		t_bucket	*next;

		while (item != NULL) {
			next = item->next;
			ht->freeFn(item->data);
			free(item);
			item = next;
		}
	}
	free(ht->buckets);
	free(ht);
}

void	*ht_add(t_ht *ht, const void *data) {
	const size_t	hash = ht->hashFn(data);
	t_bucket	**pItem = &ht->buckets[hash % ht->nBuckets];
	
	while (*pItem != NULL) {
		if (!ht->cmpFn((*pItem)->data, data))
			return ((*pItem)->data);
		pItem = &((*pItem)->next);
	}
	t_bucket	*new = calloc(1, sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->data = ht->dupFn(data);
	if (new->data == NULL) {
		free(new);
		return (NULL);
	}
	*pItem = new;
	++ht->nItems;
	return (new->data);
}

void	ht_rm(t_ht *ht, const void *data) {
	const size_t	hash = ht->hashFn(data);
	t_bucket	**pItem = &ht->buckets[hash % ht->nBuckets];
	
	while (*pItem != NULL) {
		if (!ht->cmpFn((*pItem)->data, data)) {
			t_bucket	*item = *pItem;

			*pItem = item->next;
			ht->freeFn(item->data);
			free(item);
			--ht->nItems;
			return ;
		}
	}
}

void	*ht_get(t_ht *ht, const void *data) {
	const size_t	hash = ht->hashFn(data);
	t_bucket	*item = ht->buckets[hash % ht->nBuckets];

	while (item != NULL) {
		if (!ht->cmpFn(item->data, data))
			return (item->data);
		item = item->next;
	}
	return (NULL);
}
