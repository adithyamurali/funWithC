#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

/* Server struct. */
typedef struct server {
	queue_t wq; /* Server's synchronized queue struct. */
	int num_producers;
	int num_consumers;
	int num_sleep_p;
	int num_sleep_c;
} server_t;

/* Initializes server struct and the work queue. */
void server_init(server_t * server, int num_producers, int num_consumers, 
	int num_sleep_p, int num_sleep_c);

/* Mallocs and creates Producer-Consumer threads. Sleeps indefinitely. */
void server_run(server_t * server);

/* Handle function for consumer threads. */
void *consumer_handle(void * aux);

/* Handle function for producer threads. */
void *producer_handle(void * aux);
