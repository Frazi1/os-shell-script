#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include "structs.h"
#include "linked_list.h"

#define GNOMES_CNT 3
#define DEERS_CNT 2
#define MEETING_TIME 2
#define SHIPPING_TIME 3
int deers_cnt = DEERS_CNT;
int gnomes_cnt = GNOMES_CNT;
int gnomes_to_wake;


//void * func1(const int *arg) {
//    gnome a = NULL;
//    int a =  *arg;
//    printf("%d ", a);
//    sleep(1);
//    a++;
//    printf("%d ", a);
//    pthread_exit(NULL);
//}

//int main() {
//    pthread_t f1_thread, f2_thread;
//    int i1 = 1, i2 = 2;
//    pthread_create(&f1_thread, NULL, (void *(*)(void *)) func1, &i1);
//    pthread_join(f1_thread, NULL);
//    return 0;
//}

int main() {
    linked_list_t list = empty_list();
    int a = 1;
    int b = 32;
    add(&list, &a);
    add(&list, &b);
    printf("%d\n", (*(int*) pop(&list)));
    printf("%d\n", (*(int*) pop(&list)));
    return 0;
}

