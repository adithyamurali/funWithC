#include "queue.h"

void queue_init(queue_t * queue) {
	queue->head = NULL;
	pthread_mutex_init(&queue->mutex, NULL);
	pthread_cond_init(&queue->cv, NULL);	
}

void queue_push(queue_t * queue, void * item) {
	pthread_mutex_lock(&queue->mutex);

	queue_item_t * new_item;
	new_item = (queue_item_t *) malloc(sizeof (queue_item_t));
	new_item->item = item;

	if (queue->head == NULL) {
		queue->tail = new_item;
		queue->head = new_item;

		new_item->prev = queue->tail;

	} else {
		queue->head->next = new_item;
		new_item->next = queue->head;
		queue->head = new_item;
	}

	pthread_cond_signal(&queue->cv);
	pthread_mutex_unlock(&queue->mutex);
}

queue_item_t * queue_pop(queue_t * queue) {
	pthread_mutex_lock(&queue->mutex);
	while (queue->tail == NULL) { 
		pthread_cond_wait(&queue->cv, &queue->mutex);
	}
	queue_item_t * popped_item = queue->tail;
	queue->tail = popped_item->next;

	if (queue->tail == queue->head) {
		queue->tail = NULL;
		queue->head = NULL;		
	}
	// By right, need to free the malloced struct...

	pthread_mutex_unlock(&queue->mutex);
	return popped_item;
}
