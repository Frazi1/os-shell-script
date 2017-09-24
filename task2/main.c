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
    if (fork()) {
        //parent
        dup2(fd[1], 1);

        close(fd[1]);
//        if (fd[1] != 1) {
//        }
        pf();
    } else {
        //child
        dup2(fd[0], 0);

        close(fd[0]);
//        if (fd[0] != 0) {
//        }
        chf();
    }
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
//    execlp("sed", "/bin/sed", "s/:[0-9][0-9]:[0-9][0-9]:[0-9][0-9]//g", (char *) NULL);
    char *command[3] = {"sed", "s/:[0-9][0-9]:[0-9][0-9]:[0-9][0-9]//g", NULL};
    execvp(command[0], command);
}

void reformat_date(){
    char* command[3] = {"sed", "s/\\//-/g", NULL};
    execvp(command[0],command);
}

void find_errcode4(){
    char* commmand[3]
}

void pipe5(){
    create_pipe(reformat_date, pipe6);
}

void pipe4() {
    create_pipe(remove_time_from_date, pipe5);
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

    pipe1();
    return 0;
}