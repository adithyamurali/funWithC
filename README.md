Fun with C
----------

This repo contains code for:
1) Reader-Writer Concurrency problem (reformulated as a Consumer-Producer problem) implemented with POSIX Pthreads in C<br />
2) Synchronized doubly-linked queue<br />
3) Implementations of Unix command line tools in C<br />

To Run #1 above:<br />
Example: ./main 3 2 1 1

./main <# producer threads> <# consumer threads> <# seconds of producer sleep time/iteration> <# seconds of consumer sleep time/iteration>

Program output:<br />
<Consumer/Producer> <pthread id>: <Item #>

<br />
To Compile: <br />
make all
make clean