#include <string.h>
#include <stdlib.h>

#include "hash.h"

int hash_string(const char *key)
{
	int hkey = 0;
	while (*key)
		hkey = hkey * 37 + *key++;

	return hkey;
}

void init_hash(struct hashTable *t)
{
	*t->buckets = malloc(sizeof(struct hashBucket *));
}


int hash_store(struct hashBucket *data, struct hashTable *store)
{
	int try, hkey;
	if (!store->size)
		store->size = 0;

	if (store->size == store->max)
		return 0;

	for (try = 0; 1; try++)
	{
		hkey = hash_string(data->key);
		store->buckets[hkey] = malloc(sizeof(struct hashBucket *));
		store->buckets[hkey] = data;
		store->size++;
	}
	return 0;
}

struct hashBucket *hash_retrieve(const char *key, struct hashTable *store)
{
	int try, hkey;
	for (try = 0; 1; try++)
	{
		hkey = hash_string(key);
		if (store->buckets[hkey] == NULL)
			return 0;

		if (strcmp(store->buckets[hkey]->key, key))
			return store->buckets[hkey];
	}
	return 0;
}

int hash_remove(const char *key, struct hashTable *store)
{
	int try, hkey;
	for (try = 0; 1; try++)
	{
		hkey = hash_string(key);
		if (store->buckets[hkey] == NULL)
			return 0;

		if (strcmp(store->buckets[hkey]->key, key))
		{
			store->size--;
			store->buckets[hkey] = 0;
		}
	}
	return 0;
}
