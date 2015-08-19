#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

#define L_CHILD(x) 2 * x + 1
#define R_CHILD(x) 2 * x + 2
#define PARENT(x) x / 2

struct node_ {
	int length;
	int arrival;
	int index;	
};

typedef struct node_ node;

struct heap_ {
	int size;
	node * elem;
};

typedef struct heap_ heap;

void heap_init(heap * hp) {
	hp->size = 0;
}

void swap(node * node1, node * node2) {
    node temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

void heap_insert(heap * hp, int val_params[]) {
	if (hp->size) {
		hp->elem = realloc(hp->elem, (hp->size + 1) * sizeof(node));
	} else {
		hp->elem = malloc(sizeof(node));
	}

	/* Initializing node. */
	node new_node;
	new_node.length = val_params[0];
	new_node.arrival = val_params[1];
	new_node.index = val_params[2];

	int i = (hp->size)++;
	while (i && new_node.length < hp->elem[PARENT(i)].length) {
		hp->elem[i] = hp->elem[PARENT(i)];
		i = PARENT(i);
	}
	hp->elem[i] = new_node;
}

void heapify(heap * hp, int i) {
	int smaller_index;
	smaller_index = (hp->elem[L_CHILD(i)].length < hp->elem[i].length && L_CHILD(i) < hp->size) ? L_CHILD(i) : i;
	smaller_index = (hp->elem[R_CHILD(i)].length < hp->elem[i].length && R_CHILD(i) < hp->size) 
		? R_CHILD(i) : smaller_index;
	if (smaller_index != i) {
		swap(&(hp->elem[smaller_index]), &(hp->elem[i]));
		heapify(hp, smaller_index);
	}
}

node * heap_delete_min(heap * hp) {
	node * min_node = (node *) malloc(sizeof (node));
	memcpy(min_node, &(hp->elem[0]), sizeof(node));
	hp->elem = realloc(hp->elem, hp->size * sizeof(node));
	heapify(hp, 0);
	return min_node;
}

int run(int arrival[], int length[], int N) {
	int time_to_completion = 0;
	int num_customers_served = -1;

	int i = 0;
	int t = 0;

	int log_in[N];
	int log_out[N];

	heap * hp = (heap *) malloc(sizeof(heap));
	heap_init(hp);

	while(1) {
		printf("t: %d\n", t);
		if (arrival[i] == t) {
			log_in[i] = t;
			int params[3] = {length[i], t, i};
			heap_insert(hp, params);
			i++;
		}
		if (time_to_completion == 0) {
			node * elem = heap_delete_min(hp);
			log_out[elem->index] = t + elem->length;
			time_to_completion = elem->length;
			free(elem);
			num_customers_served++;
		} else {
			time_to_completion--;
		}
		t++;
		if (num_customers_served == N) {
			break;
		}
	}

	int total_WT = 0;
	for (i = 0; i < N; i++) {
		printf("Log_in %d\n", log_in[i]);
		printf("Log_out %d\n", log_out[i]);
		total_WT += log_out[i] - log_in[i];
	}
	return total_WT / N;
}

int main(int argc, char * argv[]) {

	int N = 3;
	int arrival[3] = {0, 1, 2};
	int length[3] = {3, 9, 6};

	printf("AWT: %d\n", run(arrival, length, N));

	return EXIT_SUCCESS;
}