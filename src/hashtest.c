#include <stdio.h>
#include <stdlib.h>

#include "hash.h"

int main()
{
	struct hashTable *table;
	table = (struct hashTable *)malloc(sizeof(*table));

	struct hashBucket *test;
	test->key = "test";
	test->value = "win";

	hash_store(test, table);
	test = 0;

	struct hashBucket *tt;
	tt = hash_retrieve("test", table);

	printf("test: %s\n", tt->value);
	return 0;
}
