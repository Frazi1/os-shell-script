#ifndef TASK4_STRUCTS_H
#define TASK4_STRUCTS_H

#include <sys/types.h>

typedef struct gnome_struct {
    int id;
    pthread_t* gnome_thread;
} gnome;

typedef struct deer_struct {
    int id;
    pthread_t* deer_thread;
} deer;

#endif //TASK4_STRUCTS_H
