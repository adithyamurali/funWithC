Fun with C
----------

This repo contains code for:
1) Reader-Writer Concurrency problem (reformulated as a Consumer-Producer problem) implemented with POSIX Pthreads in C
2) Synchronized doubly-linked queue
3) Implementations of Unix command line tools in C

To Run #1 above:
Example: ./main 3 2 1 1

./main <# producer threads> <# consumer threads> <# seconds of producer sleep time/iteration> <# seconds of consumer sleep time/iteration>

Program output:
<Consumer/Producer> <pthread id>: <Item #>