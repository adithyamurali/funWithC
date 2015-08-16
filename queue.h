#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

/* Single item struct in queue. */
struct queue_item {
	void * item;
	struct queue_item * prev;
	struct queue_item * next;
};

/* Redefinition for ease. */
typedef struct queue_item queue_item_t;

/* Main Synchronous Queue stuct implemented as Doubly-Linked list
with condition variables. */
struct queue_ {
	queue_item_t * head;
	queue_item_t * tail;
	pthread_mutex_t mutex;
	pthread_cond_t cv;
};

/* Redefinition for ease. */
typedef struct queue_ queue_t;

/* Initializes the Doubly-Linked list and synchronization primitives. */
void queue_init(queue_t * queue);

/* Synchronously pushs item into list head, using
   monitors and Condition variables. */
void queue_push(queue_t * queue, void * item);

/* Synchronously pops item from list tail, using
   monitors and Condition variables. */
queue_item_t * queue_pop(queue_t * queue);
