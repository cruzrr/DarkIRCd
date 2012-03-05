#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#define _XOPEN_SOURCE 500

int main()
{
	struct hashTable *table = malloc(sizeof(struct hashTable *));
	table->max = 5000;
	init_hash(table);


	struct hashBucket *test = malloc(sizeof(struct hashBucket *));
	test->key = strdup("test");
	test->value = strdup("win");

	hash_store(test, table);
	test = 0;

	struct hashBucket *tt = malloc(sizeof(struct hashBucket *));
	tt = hash_retrieve("test", table);

	printf("test: %s\n", tt->value);
	return 0;
}
