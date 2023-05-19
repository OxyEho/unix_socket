#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

#define CONF "config"
#define MAX_SOCK_NAME 100
#define MAX_READ 11

char* get_sock_name() {
    FILE* conf_f = fopen(CONF, "r");
    char* sock_name = malloc(MAX_SOCK_NAME);
    fgets(sock_name, MAX_SOCK_NAME, conf_f);
    int path_len = snprintf(NULL, 0, "/tmp/%s", sock_name);
    char* sock_path = malloc(path_len+1);
    snprintf(sock_path, path_len+1, "/tmp/%s", sock_name);
    free(sock_name);
    return sock_path;
}

int main(int argc, char** argv) {
    char* sock_name = get_sock_name();

    struct sockaddr_un sockaddr;
    memset(&sockaddr, 0, sizeof(struct sockaddr_un));
    int sock_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        perror("can't create socket");
        exit(-1);
    }

    sockaddr.sun_family = AF_UNIX;
    strcpy(sockaddr.sun_path, sock_name);
    if (connect(sock_fd, (struct sockaddr*) &sockaddr, sizeof(sockaddr)) == -1){
        perror("can't connect to server");
        exit(-1);
    }

    for (int i = 0; i < MAX_READ; i++) {
        char send_buf[MAX_READ] = {0};
        char recv_buf[MAX_READ] = {0};
        scanf("%s", send_buf);
        write(sock_fd, send_buf, strlen(send_buf));
        read(sock_fd, recv_buf, MAX_READ);
        printf("recv: %s\n", recv_buf);
    }
    close(sock_fd);

    return 0;
}
