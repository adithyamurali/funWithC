#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

struct queue_item_ {
	void * item;
	struct queue_item * prev;
	struct queue_item * next;
};

typedef struct queue_item_ queue_item_t;

struct queue_ {
	queue_item_t * head;
	queue_item_t * tail;
	pthread_mutex_t mutex;
	pthread_cond_t cv;
};

typedef struct queue_ queue_t;

void queue_init(queue_t * queue);

void queue_push(queue_t * queue, void * item);

queue_item_t * queue_pop(queue_t * queue);
