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

/* define each event's numer here */

#define IRC_CLIENT_CONNECT 1


#endif
