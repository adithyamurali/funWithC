#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define BUF_SIZE 1024

/* Reads from fd_read and immediately writes to fd_write without delay */
bool read_write(int fd_read, int fd_write) {
	char buffer[BUF_SIZE];

	if (read(fd_read, buffer, BUF_SIZE) < 0) {
		return false;
	}

	if (write(fd_write, buffer, BUF_SIZE) < 0) {
		return false;
	}

	return true;
}

int main(int argc, char * argv[]) {

	if (argc == 1) {
		printf("Please specify at least one file!\n");
		return EXIT_FAILURE;
	}

	int i = 0;
	bool success = true;
	int fd;
	char * fname;
	
	for (;i < argc; i++) {
		fname = argv[i];
		fd = open(fname, O_RDONLY);
		if (fd < 0) {
			success = false;
			continue;
		}
		if (!read_write(fd, STDOUT_FILENO)) {
			success = false;
		}
		close(fd);
	}
	return success ? EXIT_SUCCESS : EXIT_FAILURE;
}