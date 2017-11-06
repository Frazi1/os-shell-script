#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include "structs.h"
#include "linked_list.h"

#define GNOMES_CNT 6
#define DEERS_CNT 10
#define GNOMES_TO_WAKE 4
#define SANTA_MEETING_TIME 3
#define SANTA_SLEEPING_TIME 1
#define SANTA_SHIPPING_TIME 6
#define SANTA_PREPARATION_TIME 1
#define GNOME_SLEEPING_TIME_MAX 30
#define GNOME_SLEEPING_TIME_MIN 7
#define DEER_SLEEPING_TIME_MIN 10
#define DEER_SLEEPING_TIME_MAX 30

//global vars

int deers_cnt = DEERS_CNT;
int gnomes_cnt = GNOMES_CNT;
int gnomes_to_wake = GNOMES_TO_WAKE ;
linked_list_t gnomes_queue, deers_queue;
gnome_t gnomes[256];
deer_t deers[256];
santa_t santa;

//func declarations
void santa_thread(santa_t* santa) ;
int gnome_thread(gnome_t* gnome) ;
int random_number(int min_num, int max_num);
void create_gnomes(int count);
void signal_santa();
void create_deers(int count);
void print_deers_msg(const int* id);
void print_gnome_msg(const int id);

int santa_go_with_deers(int *sleeping);

int santa_meet_gnomes(int *sleeping);

bool deers_ready();

bool gnomes_ready();

int main() {
    gnomes_queue = empty_list();
    deers_queue = empty_list();
    santa = get_santa();

    create_gnomes(gnomes_cnt);
    create_deers(deers_cnt);
    pthread_create(&(santa.pthread), NULL, (void *(*)(void *)) santa_thread, &santa);

    pthread_join(santa.pthread, NULL);
    for (int i = 0; i < GNOMES_CNT; ++i) {
        pthread_join(gnomes[i].pthread, NULL);
    }
    for (int i = 0; i < deers_cnt; ++i) {
        pthread_join(deers[i].pthread, NULL);
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
//        printf("gnome %d waiting for santa\n", gnome->id);
        print_gnome_msg(gnome->id);
        signal_santa();
        while(pthread_cond_wait(&(gnome->cond), &(gnome->mutex)));
        pthread_mutex_unlock(&(gnome->mutex));
    }
    pthread_exit(0);
}

void deer_thread(deer_t* deer) {
    srand((unsigned int) (time(NULL) + 31 * deer->id));
    while(1) {
        sleep(random_number(DEER_SLEEPING_TIME_MIN,
                            DEER_SLEEPING_TIME_MAX));
        add(&deers_queue, deer);
        pthread_mutex_lock(&deer->mutex);
        print_deers_msg(&deer->id);

        signal_santa();
        pthread_cond_wait(&deer->cond, &deer->mutex);
        pthread_mutex_unlock(&deer->mutex);
    }
}

void santa_thread(santa_t* santa) {

    srand((unsigned int) (time(NULL) + 29));
    int sleeping = 0;
    santa_sleep(&sleeping);
    while(1) {
        pthread_mutex_lock(&santa->mutex);
        pthread_cond_wait(&santa->door_bell, &santa->mutex);
        //go with deers
        if(deers_ready()) {
            sleeping = santa_go_with_deers(&sleeping);
            if(gnomes_ready())
                sleeping = santa_meet_gnomes(&sleeping);
        }
        //end deers
        //meet gnomes
        if(gnomes_ready()) {
            sleeping = santa_meet_gnomes(&sleeping);
            if(deers_ready())
                sleeping = santa_go_with_deers(&sleeping);
            //end meet gnomes
        }
        santa_sleep(&sleeping);
        pthread_mutex_unlock(&santa->mutex);
    }
    pthread_exit(0);
}

bool gnomes_ready() { return gnomes_queue.count >= gnomes_to_wake; }

bool deers_ready() { return deers_queue.count == deers_cnt; }

int santa_meet_gnomes(int *sleeping) {
    santa_wake(sleeping, gnomes_wake);
    pthread_mutex_lock(&gnomes_queue.mutex);
    while(gnomes_queue.count > 0) {
                sleep(SANTA_PREPARATION_TIME);
                gnome_t* gnome = (gnome_t*) pop_unsafe(&gnomes_queue);
                printf("Santa meets gnome %d\n", gnome->id);
                sleep(SANTA_MEETING_TIME);
                pthread_cond_signal(&gnome->cond);
            }
    pthread_mutex_unlock(&gnomes_queue.mutex);
    return (*sleeping);
}

int santa_go_with_deers(int *sleeping) {
    santa_wake(sleeping, deers_wake);
    pthread_mutex_lock(&deers_queue.mutex);
    printf("santa is shipping presents with deers \n");
    sleep(SANTA_SHIPPING_TIME);
    while(deers_queue.count > 0) {
                deer_t* deer = pop_unsafe(&deers_queue);
                pthread_cond_signal(&deer->cond);
            }
    printf("Santa releases his deers.\n");
    pthread_mutex_unlock(&deers_queue.mutex);
    return (*sleeping);
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

void create_deers(int count) {
    for (int i = 0; i < count; ++i) {
        deers[i] = get_deer(i+1);
        pthread_create(&deers[i].pthread, NULL, (void *(*)(void *)) deer_thread, &deers[i]);
    }
}

void signal_santa(){
//    pthread_mutex_lock(&santa.mutex);
    if(gnomes_queue.count >= gnomes_to_wake || deers_queue.count == deers_cnt) {
        pthread_cond_signal(&santa.door_bell);
    }
//    pthread_mutex_unlock(&santa.mutex);
}

void santa_sleep(int* sleeping) {
    if(*sleeping == 0) {
        *sleeping = 1;
        printf("Santa is sleeping.\n");
        sleep(SANTA_SLEEPING_TIME);
    }
}

void santa_wake(int* sleeping, enum reason_t reason){
    *sleeping = 0;
    if(reason == gnomes_wake){
        printf("Gnomes wake santa.\n");
    }
    if(reason == deers_wake){
        printf("Deers wake santa.\n");
    }
}

void print_deers_msg(const int* id){
    printf("Deer %d is waiting for santa. %d/%d deers are waiting\n",
           *id, deers_queue.count, deers_cnt);
}

void print_gnome_msg(const int id) {
    printf("Gnome %d is waiting for santa. %d/%d gnomes to wake santa.\n",
            id, gnomes_queue.count, GNOMES_TO_WAKE);
}