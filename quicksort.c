#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

struct node_ {
    int val;
    struct node_ * next;
};

typedef struct node_ node_t;
 
struct list_ {
    node_t * head;
    int size;
};

typedef struct list_ list_t;

void list_init(list_t * list) {
    list->head = NULL;
    list->size = 0;
}    
    
void list_append(list_t * list, int val) {
    node_t * new_node = (node_t *) malloc(sizeof(node_t));
    new_node->val = val;
    new_node->next = NULL;
    (list->size)++;
    if (!list->head) {
        list->head = new_node;
    } else {
        node_t * curr_head = list->head;
        new_node->next = curr_head;
        list->head = new_node;
    }
}

void list_iterate_and_print(list_t * list) {
    node_t * curr_node = list->head;
    while (curr_node) {
        printf("%d ",curr_node->val);
        curr_node = curr_node->next;
    }
}

void list_array(list_t * list) {
    int arra
    node_t * curr_node = list->head;
    while (curr_node) {
        printf("%d ",curr_node->val);
        curr_node = curr_node->next;
    }
}

void partition(int ar_size, int *  ar) {
    list_t * higher_list = (list_t *) malloc(sizeof(list_t));
    list_t * lower_list = (list_t *) malloc(sizeof(list_t));
    list_init(higher_list);
    list_init(lower_list);

    int p = ar[0];
    int i = 1;

    for (; i < ar_size; i++) {
        int elem = ar[i];
        if (elem <= p) {
            list_append(lower_list, elem);
        } else {
            list_append(higher_list, elem);
        }
    }

    list_iterate_and_print(lower_list);
    printf("%d ", p);
    list_iterate_and_print(higher_list);
    printf("\n");
}

int main(void) {

    int _ar_size;
    scanf("%d", &_ar_size);
    int _ar[_ar_size], _ar_i;

    for(_ar_i = 0; _ar_i < _ar_size; _ar_i++) { 
       scanf("%d", &_ar[_ar_i]); 
    }

    partition(_ar_size, _ar);

    return 0;
}