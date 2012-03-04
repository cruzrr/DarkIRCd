#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "event.h"
#include "hash.h"

struct eventsTable *events = NULL;

int hash_read(int key, int try, int max)
{
	return (key + try) % max;
}

int hashTable_insert(struct hashRow *data, struct event_hashTable *hash_table)
{
	int try, hash;
	if (hash_table->number_of_elements < hash_table->max)
		return 0;	// the table has reached it's limit

	for (try = 0; 1; try++)
	{
		hash = hash_read(data->key, try, hash_table->max);
		if (hash_table->elements[hash] == 0)
		{
			hash_table->elemtent[hash] = data;
			hash_table->number_of_elements++;
			return 1;
		}
	}
	return 0;
}

struct hashRow *hash_get(int key, struct event_hashTable *hash_table)
{
	int try, hash;
	for (try = 0; 1; try++)
	{
		hash = hash_read(key, try, hash_table->max);
		if (hash_table->elements[hash] == 0)
			return 0;

		if (hash_table->elements[hash]->key == key)
			return hash_table->elements[hash];
	}
	return 0;
}

int hash_delete(int key, struct event_hashTable *hash_table)
{
	int try, hash;
	for (try = 0; 1; try++)
	{
		hash = hash_read(key, try, hash_table->max);
		if (hash_table->elements[hash] == 0)
			return 0;

		if (hash_table->elements[hash]->key == key)
		{
			hash_table->number_of_elements--;
			hash_table->elements[hash] = 0;
			return 1;
		}
	}
	return 0;
}

void registerHook(int key, void (*callback)(void *))
{
	if (!events)
	{
		perror("hash table hasn't init'd.");
		exit(1);
	}

	struct hashRow *toInsert;
	hashRow.key =  key;
	hashRow.cb  =  callback;
}


int init_events()
{
	events = NULL;
}
