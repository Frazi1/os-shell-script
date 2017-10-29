#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "structs.h"
#include "linked_list.h"

#define GNOMES_CNT 4
#define DEERS_CNT 2
#define GNOMES_TO_WAKE 2
#define SANTA_MEETING_TIME 2
#define SANTA_SLEEPING_TIME 1
#define SANTA_SHIPPING_TIME 4
#define SANTA_PREPARATION_TIME 1
#define GNOME_SLEEPING_TIME_MAX 12
#define GNOME_SLEEPING_TIME_MIN 7
#define DEER_SLEEPING_TIME_MIN 5
#define DEER_SLEEPING_TIME_MAX 10

//global vars

int deers_cnt = DEERS_CNT;
int gnomes_cnt = GNOMES_CNT;
int gnomes_to_wake = GNOMES_TO_WAKE ;
linked_list_t gnomes_queue, deers_queue;
gnome_t gnomes[GNOMES_CNT];
santa_t santa;

//func declarations
void santa_thread(santa_t* santa) ;
int gnome_thread(gnome_t* gnome) ;
int random_number(int min_num, int max_num);
void create_gnomes(int count);
void signal_santa(enum reason_t reason);



int main() {
    gnomes_queue = empty_list();
    deers_queue = empty_list();
    santa = get_santa();

    create_gnomes(gnomes_cnt);
    pthread_create(&(santa.pthread), NULL, (void *(*)(void *)) santa_thread, &santa);

    pthread_join(santa.pthread, NULL);
    for (int i = 0; i < GNOMES_CNT; ++i) {
        pthread_join(gnomes[i].pthread, NULL);
    }
    return 0;
}

int gnome_thread(gnome_t* gnome) {
    srand(time(NULL) + gnome->id);
    while(1){
        sleep(random_number(GNOME_SLEEPING_TIME_MIN,
                            GNOME_SLEEPING_TIME_MAX));
        add(&gnomes_queue, gnome);
        pthread_mutex_lock(&(gnome->mutex));
        printf("gnome %d waiting for santa\n", gnome->id);
        signal_santa(gnomes_wake);
        while(pthread_cond_wait(&(gnome->cond), &(gnome->mutex)));
        pthread_mutex_unlock(&(gnome->mutex));
    }
    pthread_exit(0);
}

void santa_thread(santa_t* santa) {

    srand((unsigned int) (time(NULL) + 29));
    int sleeping = 0;
    santa_sleep(&sleeping);
    while(1) {
        pthread_mutex_lock(&santa->mutex);
        pthread_cond_wait(&santa->door_bell, &santa->mutex);
        if(gnomes_queue.count >= gnomes_to_wake ) {
            santa_wake(&sleeping, gnomes_wake);
            pthread_mutex_lock(&gnomes_queue.mutex);
            while(gnomes_queue.count > 0) {
                sleep(SANTA_PREPARATION_TIME);
                gnome_t* gnome = (gnome_t*) pop_unsafe(&gnomes_queue);
                printf("santa meets gnome %d\n", gnome->id);
                sleep(SANTA_MEETING_TIME);
                pthread_cond_signal(&gnome->cond);
            }
            pthread_mutex_unlock(&gnomes_queue.mutex);
        }
        santa_sleep(&sleeping);
        pthread_mutex_unlock(&santa->mutex);
    }
    pthread_exit(0);
}

int random_number(int min_num, int max_num)
{
    int result = 0, low_num = 0, hi_num = 0;

    if (min_num < max_num)
    {
        low_num = min_num;
        hi_num = max_num + 1; // include max_num in output
    } else {
        low_num = max_num + 1; // include max_num in output
        hi_num = min_num;
    }

//    srand(time(NULL));
    result = (rand() % (hi_num - low_num)) + low_num;
    return result;
}

void create_gnomes(int count){
    for (int i = 0; i < count; ++i) {
        gnomes[i] = get_gnome(i+1);
        pthread_create(&(gnomes[i].pthread), NULL, (void *(*)(void *)) gnome_thread, &(gnomes[i]));
    }
}

void signal_santa(enum reason_t reason){
    pthread_mutex_lock(&santa.mutex);
    if(gnomes_queue.count >= gnomes_to_wake){
        pthread_cond_signal(&santa.door_bell);
    }
    pthread_mutex_unlock(&santa.mutex);
}

void santa_sleep(int* sleeping) {
    if(*sleeping == 0){
        *sleeping = 1;
        printf("santa sleeping\n");
        sleep(SANTA_SLEEPING_TIME);
    }
}

void santa_wake(int* sleeping, enum reason_t reason){
    *sleeping = 0;
    if(reason == gnomes_wake){
        printf("gnomes wake santa\n");
    }
    if(reason == deers_wake){
        printf("deers wake santa\n");
    }
}