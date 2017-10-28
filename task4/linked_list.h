#ifndef TASK4_LINKED_LIST_H
#define TASK4_LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct list_list {
    pthread_mutex_t mutex;
    struct node *head;
    int count;
} linked_list_t;

typedef struct node {
    void* value;
    struct node *next;
} node_t;


//void add(node_t* head, void* item);
void add(linked_list_t *list, void *item);
void print_list(linked_list_t* head);
void* pop(linked_list_t* list);
linked_list_t empty_list();
#endif //TASK4_LINKED_LIST_H
