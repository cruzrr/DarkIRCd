#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"

int main()
{
	struct hashTable *table;
	table->max = 5000;

	hash_alloc(table, 5000);

	struct hashBucket *test;
	test->key = strdup("test");
	test->value = strdup("win");

	hash_store(test, table);
	test = 0;

	struct hashBucket *tt;
	tt = hash_retrieve("test", table);

	printf("test: %s\n", tt->value);
	return 0;
}
