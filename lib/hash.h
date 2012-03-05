#ifndef HASH_H
#define HASH_H

struct hashBucket
{
	const char *key;
	char *value;
};

struct hashTable
{
	int max;
	int size;
	struct hashBucket *buckets[];
};


void init_hash(struct hashTable *t);
int hash_store(struct hashBucket *data, struct hashTable *store);
struct hashBucket *hash_retrieve(const char *key, struct hashTable *store);
int hash_remove(const char *key, struct hashTable *store);

#endif
