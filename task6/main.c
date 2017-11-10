#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

int get_strlen(char* str) {
    int n = 0;
    while(str[n] != '\0') n++;
    return n;
}

int main(int argc, char *argv[]) {
    int sockfd, port;
    struct sockaddr_un serv_addr;
    char *path = argv[1];
    char* key = argv[2];
    printf("key: %s, lenght: %d", key, (int) sizeof(key));
    char* value = argv[3];

    char buffer[256];

    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if(sockfd < 0) {
        printf("ERROR");
        exit(1);
    }
    serv_addr.sun_family = AF_UNIX;
    strcpy(serv_addr.sun_path, "/home/dmitry/fkn/os/task6/socket1");

    if(connect(sockfd, (const struct sockaddr *) &serv_addr, sizeof(serv_addr))) {
        printf("ERROR connection");
        perror("123");
        exit(1);
    }

    int n;
    char command[2];
    command[0] = 0xC8;
    command[1] = 0x10;
//    char key[] = "test";
//    char value[] = "kets";
    int key_size = htonl((uint32_t) get_strlen(key));
    int value_size = htonl((uint32_t) get_strlen(value));
    printf("sizeof key %d\n", ntohl((uint32_t) key_size) );
    printf("sizeof value %d\n", ntohl((uint32_t) value_size));

    printf("%d\n", (int) sizeof(char));
    n = (int) write(sockfd, command, sizeof(command));
    printf("written command bytes %d\n", n);

    n = (int) write(sockfd, &key_size, sizeof(key_size));
    printf("written key size:%d, bytes %d\n", ntohl((uint32_t) key_size) , n);

    n = (int) write(sockfd, &value_size , sizeof(value_size));
    printf("written value size: %d, bytes %d\n", ntohl((uint32_t) value_size), n);

//    n = (int) write(sockfd, key, sizeof(key));
//    printf("written key %d\n", n);
//    n = (int) write(sockfd, value, sizeof(value));
//    printf("written value %d\n", n);

//    write_buf(sockfd, key, ntohl((uint32_t) key_size));
//    write_buf(sockfd, value, ntohl((uint32_t) value_size));

    send(sockfd, key, ntohl((uint32_t) key_size), 0);
    send(sockfd, value, ntohl((uint32_t) value_size), 0);
    if(n < 0) {
        printf("ERROR writing to socket");
        exit(1);
    }
    bzero(buffer, 256);
    n = (int) read(sockfd, buffer, 1);
    if (n < 0 ) {
        printf("ERROR reading from socket");
        exit(1);
    }
    printf("Response: %s\n", buffer);
    close(sockfd);
    return 0;
}