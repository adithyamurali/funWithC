#include "queue.h"

/* Initializes the Doubly-Linked list and synchronization primitives. */
void queue_init(queue_t * queue) {
	queue->head = NULL;
	queue->tail = NULL;
	pthread_mutex_init(&queue->mutex, NULL);
	pthread_cond_init(&queue->cv, NULL);	
}

/* Synchronously pushs item into list head, using
   monitors and Condition variables. */
void queue_push(queue_t * queue, void * item) {
	pthread_mutex_lock(&queue->mutex);

	queue_item_t * new_item;
	new_item = (queue_item_t *) malloc(sizeof (queue_item_t));
	new_item->item = item;
	new_item->prev = NULL;
	new_item->next = NULL;

	if (queue->head == NULL) {
		queue->tail = new_item;
		queue->head = new_item;

	} else {
		queue->head->next = new_item;
		new_item->prev = queue->head;
		queue->head = new_item;
	}

	pthread_cond_signal(&queue->cv);
	pthread_mutex_unlock(&queue->mutex);
}

/* Synchronously pops item from list tail, using
   monitors and Condition variables. */
queue_item_t * queue_pop(queue_t * queue) {
	pthread_mutex_lock(&queue->mutex);

	while (queue->tail == NULL) { 
		pthread_cond_wait(&queue->cv, &queue->mutex);
	}
	queue_item_t * popped_item = queue->tail;
	queue->tail = popped_item->next;

	if (popped_item->next) {
		popped_item->next->prev = NULL;
	} else {
		/* Case when Poppped item was the only item in the queue */
		queue->head = NULL;
	}

	pthread_mutex_unlock(&queue->mutex);
	return popped_item;
}
