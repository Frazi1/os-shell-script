#ifndef TASK4_STRUCTS_H
#define TASK4_STRUCTS_H

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include "structs.h"
#include <sys/types.h>

typedef struct gnome_struct {
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    pthread_t pthread;
    int id;
    int with_santa;
} gnome_t;

typedef struct deer_struct {
    pthread_cond_t cond;
    pthread_mutex_t mutex;
    pthread_t pthread;
    int id;
} deer_t;

typedef struct santa_struct {
    pthread_cond_t door_bell;
    pthread_t pthread;
    pthread_mutex_t mutex;
} santa_t;

typedef enum reason_t {
    gnomes_wake,
    deers_wake
} reason;

santa_t get_santa();
gnome_t get_gnome(int id);
deer_t get_deer(int id);
void santa_sleep(int* sleeping);
void santa_wake(int* sleeping, enum reason_t reason);
#endif //TASK4_STRUCTS_H
