#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

typedef struct server {
	queue_t wq;
	int num_producers;
	int num_consumers;
} server_t;

void server_init(server_t * server, int num_producers, int num_consumers);

void server_run(server_t * server);

void *consumer_handle(void * aux);

void *producer_handle(void * aux);
