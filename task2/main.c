#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>
#include <errno.h>

#define READ_END 0
#define WRITE_END 1



//void create_pipe(void (*prev_func)(void), void (*next_func)(void)) {
//    int fd[2];
//    pipe(fd);
//    pid_t pid = fork();
//    if(!pid){
//        //child
//        close(fd[WRITE_END]);
//        dup2(fd[READ_END], READ_END);
//        next_func();
//    } else {
//        //parent
//        close(fd[READ_END]);
//        dup2(fd[WRITE_END], STDOUT_FILENO);
//        prev_func();
//    }
//}

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
//    char *command[3] = {"awk", "{print $4, $9}", NULL};
//    execvp(command[0], command);
}

void cut(){
    execlp("cut", "cut", "-c","2-", (char*) NULL);
}

void reformat_date() {
//    execlp("sed", "/bin/sed", "s/:[0-9][0-9]:[0-9][0-9]:[0-9][0-9]//g", (char *) NULL);
    char *command[3] = {"sed", "s/:[0-9][0-9]:[0-9][0-9]:[0-9][0-9]//g", NULL};
    execvp(command[0], command);
}

void pipe3() {
//    create_pipe();
}

void pipe2() {
    create_pipe(print_date_errcode, cut);
}

void pipe1() {
    create_pipe(cat_log, pipe2);
}


int main(int argc, char **argv) {

    pipe1();
    return 0;
}


//void fork_write(const pid_t *pid, int* fd, char **command) {
//    pid = (pid_t *) fork();
//    if (!pid) {
//        dup2(fd[WRITE_END], STDOUT_FILENO);
//        close(fd[WRITE_END]);
//        execvp((const char *) command[0], command);
//        exit(EXIT_FAILURE);
//    }
//}
//
//void fork_read(const pid_t *pid, int* fd, char **command) {
//    pid = (pid_t *) fork();
//    if (pid == 0) {
//        dup2(fd[READ_END], STDIN_FILENO);
//        close(fd[READ_END]);
//        execvp(command[0], command);
//        exit(EXIT_FAILURE);
//    }
//}

//    if (pid1) {
//        dup2(fd[WRITE_END], STDOUT_FILENO);
//        printf("first");
//        char *arg[] = {"cat", "../log.txt", NULL};
//        execvp(arg[0], arg);
//        close(fd[1]);
//
//        exit(EXIT_FAILURE);
//    }

//    pid_t pid2 = fork();
//    if (pid2 == 0) {
//        dup2(fd[READ_END], STDIN_FILENO);
//        printf("second");
//        close(fd[READ_END]);
//        char* command[3] = {"awk", "{print $4, $9}", NULL};
//        execvp(command[0], command);
//    }