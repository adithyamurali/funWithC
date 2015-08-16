#include <stdio.h>
#include <stdbool.h>
#include "server.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1


/* Initializes server and runs the problem with specified
   number of produces and consumers. */
bool WriterReaderProblem(int num_p, int num_c, int sleep_p, int sleep_c) {
	server_t * server = (server_t *) malloc(sizeof(server_t));
	server_init(server, num_p, num_c, sleep_p, sleep_c);
	server_run(server);
	return true;
}


int main(int argc, char * argv[]) {
	bool success;

	int num_p = strtol(argv[1], NULL, 0);
	int num_c = strtol(argv[2], NULL, 0);
	int sleep_p = strtol(argv[3], NULL, 0);
	int sleep_c = strtol(argv[4], NULL, 0);

	success = WriterReaderProblem(num_p, num_c, sleep_p, sleep_c);

	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}