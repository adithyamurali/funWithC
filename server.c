#include <pthread.h>
#include <unistd.h>

#include "server.h"

/* Handle function for consumer threads. */
void *consumer_handle(void * aux) {
	server_t * server = (server_t *) aux;
	pthread_t thread_id;
	thread_id = pthread_self();
	while(1) {
		sleep(server->num_sleep_c);

		queue_item_t * queue_item = queue_pop(&server->wq);
		printf("Consumer %llu: %i\n", (uint64_t) thread_id, *((int *) queue_item->item));
	}
}

/* Handle function for producer threads. */
void *producer_handle(void * aux) {
	server_t * server = (server_t *) aux;
	pthread_t thread_id;
	thread_id = pthread_self();
	while(1) {
		sleep(server->num_sleep_p);

		int * item = malloc (sizeof (int));
		*item = rand() % 100;

		queue_push(&server->wq, (void * ) item); 
		printf("Producer %llu: %i\n", (uint64_t) thread_id, *item);
	}
}

/* Initializes server struct and the work queue. */
void server_init(server_t * server, int num_producers, int num_consumers, int num_sleep_p, int num_sleep_c) {
	server->num_consumers = num_consumers;
	server->num_producers = num_producers;
	server->num_sleep_p = num_sleep_p;
	server->num_sleep_c = num_sleep_c;
	queue_init(&server->wq);
}

/* Mallocs and creates Producer-Consumer threads. Sleeps indefinitely. */
void server_run(server_t * server) {

	int i;
	pthread_t *consumer_threads[server->num_consumers];
	pthread_t *producer_threads[server->num_producers];

	for (i = 0; i < server->num_consumers; i++) {
		consumer_threads[i] = malloc(sizeof(pthread_t));
		pthread_create(consumer_threads[i], NULL, &consumer_handle, (void *) server);
	}

	for (i = 0; i < server->num_producers; i++) {
		producer_threads[i] = malloc(sizeof(pthread_t));
		pthread_create(producer_threads[i], NULL, &producer_handle, (void *) server);
	}

	while(1) {
		sleep(1);
	}
}