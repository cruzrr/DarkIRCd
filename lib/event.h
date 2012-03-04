#ifndef EVENT_H
#define EVENT_H

struct hashRow
{
        int key;
        void (*cb)();
}

struct event_hashTable
{
        int max;
        int number_of_elements;
        struct hashRow **elements;
};


struct callbackList
{
	void **values;
	int count;

};

int hashTable_insert(struct hashRow *data, struct event_hashTable *hash_table);
struct hashRow *hash_get(int key, struct event_hashTable *hash_table);
int hash_delete(int key, struct event_hashTable *hash_table);
int init_events();

struct eventsTable *events;


/* define each event's numer here */

#define IRC_CLIENT_CONNECT 1


#endif
