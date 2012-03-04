#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define true 1

struct hashRow {
	char *key;
	char *value;
};

struct hash_table {
	int max;
	int number_of_elements;
	struct hashRow **elements;
};

int hashstring(const char *s)
{
	int key = 0;
	while (*s)
		key = key * 37 + *s++;

	return key;
}

int hash_fun(int key, int try, int max) {
    return (key + try) % max;
}

int hash_insert(struct hashRow *data, struct hash_table *hash_table) {
    int try, hash;
    if(hash_table->number_of_elements < hash_table->max) {
        return 0; // FULL
    }
    for(try = 0; true; try++) {
	int hkey = hashstring(data->key);
        hash = hash_fun(hkey, try, hash_table->max);
        if(hash_table->elements[hash] == 0) { // empty cell
            hash_table->elements[hash] = data;
            hash_table->number_of_elements++;
            return 1;
        }
    }
    return 0;
}

struct hashRow *hash_retrieve(char *key, struct hash_table *hash_table) {
    int try, hash;
    for(try = 0; true; try++) {
	int hkey = hashstring(key);
        hash = hash_fun(hkey, try, hash_table->max);
        if(hash_table->elements[hash] == 0) {
            return 0; // Nothing found
        }
        if(hash_table->elements[hash]->key == key) {
            return hash_table->elements[hash];
        }
    }
    return 0;
}


int hash_delete(char *key, struct hash_table *hash_table) {
    int try, hash;
    for(try = 0; true; try++) {
	int hkey = hashstring(key);
        hash = hash_fun(hkey, try, hash_table->max);
        if(hash_table->elements[hash] == 0) {
            return 0; // Nothing found
        }
        if(hash_table->elements[hash]->key == key) {
            hash_table->number_of_elements--;
            hash_table->elements[hash] = 0;
            return 1; // Success
        }
    }
    return 0;
}

struct hash_table *table;
table = malloc(sizeof(*table));

void insertsomething()
{
    struct hashRow *toInsert;
    toInsert = (struct hashRow *)malloc(sizeof(*toInsert));

    printf("toInsert declared\n");

/*
    char *k = (char*)malloc(sizeof(char*)); // wrong size
    char *v = (char*)malloc(sizeof(char*)); // wrong size

    k = "sayhello"; // bad assignment
    v = "hello";    // bad assignment
*/

    toInsert->key = strdup("sayhello");
    toInsert->value = strdup("hello");

    hash_insert(toInsert, table);
}


int main()
{
	printf("calling insertsomething.\n");
	insertsomething();
	struct hashRow *gotten;
	gotten = hash_retrieve("sayhello", table);
	printf("test: %s\n", gotten->value);
}
