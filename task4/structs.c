
#include <unistd.h>
#include "structs.h"

santa_t get_santa(){
    santa_t* santa = malloc(sizeof(santa_t));
    pthread_cond_init(&(santa->door_bell), NULL);
    pthread_mutex_init(&(santa->mutex), NULL);
    return *santa;
}

gnome_t get_gnome(int id) {
    gnome_t* gnome = malloc(sizeof(gnome_t));
    gnome->id = id;
    gnome->with_santa = 0;
    pthread_cond_init(&(gnome->cond), NULL);
    pthread_mutex_init(&(gnome->mutex), NULL);
    return *gnome;
}