#include "linked_list.h"

linked_list_t empty_list(){
    linked_list_t* list = malloc(sizeof(linked_list_t));
    pthread_mutex_init(&(list->mutex), NULL);
    return *list;
}

void add(linked_list_t *list, void *item){
    pthread_mutex_lock(&(list->mutex));
    list->count++;
    if(list->head == NULL){
        list->head = malloc(sizeof(node_t));
        list->head->value = item;
        list->head->next = NULL;
    }
    else {
        node_t *current = list->head;

        while (current->next != NULL) {
            current = current->next;
        }

        current->next = malloc(sizeof(node_t));
        current->next->value = item;
        current->next->next = NULL;
    }
    pthread_mutex_unlock(&(list->mutex));
}

void print_list(linked_list_t* list){
    node_t* current = list->head;
    while(current != NULL){

        printf("%d", *((int*) (current->value)));
        current = current->next;
    }
}

void* pop(linked_list_t* list){
    pthread_mutex_lock(&(list->mutex));
    void* result = list->head->value;
    if(list-> head == NULL || list->head->next == NULL){
        list->head = NULL;
    } else {
        list->head = list->head->next;
    }
    pthread_mutex_unlock(&(list->mutex));
    return result;
}