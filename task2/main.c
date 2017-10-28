#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1


void create_pipe(void (*pf)(void), void (*chf)(void)) {
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    printf("shit2");
    if (pid) {
        printf("shit1");
        //parent
        if (fd[1] != 1) {
            dup2(fd[1], 1);
        }
        printf("shit");
        close(fd[0]);
        close(fd[1]);
        printf("shit");
        pf();
    } else {
        //child
        printf("shit");
        if (fd[0] != 0) {
            dup2(fd[0], 0);
        }
        printf("shit");
        close(fd[0]);
        close(fd[1]);
        printf("shit");
        chf();
    }
//    close(fd[0]);
//    close(fd[1]);
    int status;
//    waitpid(pid,&status , NULL);
}

void cat_log() {
    execlp("/bin/cat", "/bin/cat", "log.txt", (char *) NULL);
}

void print_date_errcode() {
    execlp("awk", "awk", "{print $4, $9}", (char*) NULL);
}

void cut_first(){
    execlp("cut", "cut", "-c","2-", (char*) NULL);
}

void remove_time_from_date() {
    execlp("sed", "sed", "s/:[0-9][0-9]:[0-9][0-9]:[0-9][0-9]//g", (char *) NULL);
//    char *command[3] = {"sed", "s/:[0-9][0-9]:[0-9][0-9]:[0-9][0-9]//g", NULL};
//    execvp(command[0], command);
}

void reformat_date(){
    char* command[3] = {"sed", "s/\\//-/g", NULL};
    execvp(command[0],command);
}

void find_errcode(){
    execlp("grep", "grep" ,"[[:space:]]4", (char*) NULL);
//    char* command[3] = {"grep", (char *) '4', NULL};
//    execvp(command[0], command);
}

void count_uniq_dates(){
    execlp("uniq","uniq", "-c1", (char*) NULL);

}

void sort(){
    printf("TEST");
    execlp("sort", "sort", "-nrk 1", (char*) NULL);
}

void pipe7(){
    create_pipe(count_uniq_dates, sort);
}

void pipe6(){
    create_pipe(find_errcode, pipe7);
}

void pipe5(){
    create_pipe(remove_time_from_date, pipe6);
}

void pipe4() {
    create_pipe(find_errcode, pipe5);
}

void pipe3() {
    create_pipe(cut_first, pipe4);
}

void pipe2() {
    create_pipe(print_date_errcode, pipe3);
}

void pipe1() {
    create_pipe(cat_log, pipe2);
}


int main(int argc, char **argv) {
    printf("shit");
//    pipe1();
    printf("shit");
    return 0;
}