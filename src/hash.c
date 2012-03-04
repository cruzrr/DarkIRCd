#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hash.h"
#define true 1

struct hashRow {
	const char *key;
	int gkey;
	char *value;
};

struct hashTable {
	int max;
	int number_of_elements;
	struct hashRow **elements;
};

int hashstring(const char* s) {
  int key = 0;
  while (*s) {
    key = key*37 + *s++;
  }
  return key * -1;
}


int hash_fun(int key, int try) {
    return ((key + try) % 1024);
}

int hash_insert(struct hashRow *data, struct hashTable *hash_table) {
    int try, hash;
    if (!hash_table->number_of_elements)
    	hash_table->number_of_elements = 0;
    	
    if(hash_table->number_of_elements < 1024) {
        return 0; // FULL
    }
    for(try = 0; true; try++) {
	int hkey = hashstring(data->key);
	printf("hkey: %d\n", hkey);
		data->gkey = hkey;
        hash = hash_fun(hkey, try);
        if(hash_table->elements[hash] == 0) { // empty cell
            hash_table->elements[hash] = data;
            hash_table->number_of_elements++;
            return 1;
        }
    }
    return 0;
}

struct hashRow *hash_retrieve(const char *key, struct hashTable *hash_table) {
    int try, hash;
    for(try = 0; true; try++) {
		int hkey = hashstring(key);
		printf("hkey(hash_retrieve): %d\n", hkey);
        hash = hash_fun(hkey, try);
        if(hash_table->elements[hash] == 0) {
            return 0; // Nothing found
        }
        if(hash_table->elements[hash]->gkey == hkey) {
            return hash_table->elements[hash];
        }
    }
    return 0;
}


int hash_delete(const char *key, struct hashTable *hash_table) {
    int try, hash;
    for(try = 0; true; try++) {
	int hkey = hashstring(key);
	printf("hkey: %d\n", hkey);
        hash = hash_fun(hkey, try);
        if(hash_table->elements[hash] == 0) {
            return 0; // Nothing found
        }
        if(hash_table->elements[hash]->gkey == hkey) {
            hash_table->number_of_elements--;
            hash_table->elements[hash] = 0;
            return 1; // Success
        }
    }
    return 0;
}


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

    toInsert->key = strdup("s");
    toInsert->value = strdup("hello");

    hash_insert(toInsert, table);
    printf("toInsert done\n");
}


int main()
{
	table = (struct hashTable *)malloc(sizeof(struct hashTable *));
	printf("calling insertsomething.\n");
	insertsomething();
	struct hashRow *gotten;
	gotten = hash_retrieve("sayhello", table);
	printf("test: %s\n", gotten->value);
}
