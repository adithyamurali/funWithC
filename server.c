#include <pthread.h>
#include <unistd.h>

#include "server.h"

void *consumer_handle(void * aux) {
	server_t * server = (server_t *) aux;
	while(1) {
		sleep(1);
		queue_item_t * queue_item = queue_pop(&server->wq);
		printf("Consumer: %i\n", *((int *) queue_item->item));
	}
}

void *producer_handle(void * aux) {
	server_t * server = (server_t *) aux;
	while(1) {
		sleep(5);
		int * item = malloc (sizeof (int));
		*item = rand() % 100;
		queue_push(&server->wq, (void * ) item); 
		printf("Producer: %i\n", *item);
	}
}

void server_init(server_t * server, int num_producers, int num_consumers) {
	server->num_consumers = num_consumers;
	server->num_producers = num_producers;
	queue_init(&server->wq);
}

void server_run(server_t * server) {

	int i;
	pthread_t *consumer_threads[2];
	pthread_t *producer_threads[2];

	for (i = 0; i < 2; i++) {
		consumer_threads[i] = malloc(sizeof(pthread_t));
		pthread_create(consumer_threads[i], NULL, &consumer_handle, (void *) server);
	}

	for (i = 0; i < 2; i++) {
		producer_threads[i] = malloc(sizeof(pthread_t));
		pthread_create(producer_threads[i], NULL, &producer_handle, (void *) server);
	}

	while(1) {
		sleep(1);
	}
}