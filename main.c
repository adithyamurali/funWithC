#include <stdio.h>
#include <stdbool.h>
#include "server.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

bool test1() {
	server_t * server = (server_t *) malloc(sizeof(server_t));
	server_init(server, 2, 2);
	server_run(server);
	return true;
}


int main(int argc, char * argv[]) {
	bool success;

	success = test1();

	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}