// https://csperkins.org/teaching/2007-2008/networked-systems/lecture04.pdf
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
    return 0;
}

void client() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        fprintf(stderr, "couldnt create socket (%d)\n", errno);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    inet_pton(AF_INET, "192.0.0.1", &addr.sin_addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);

    if(connect(fd, (struct sockaddr *)&addr, sizeof addr) == -1) {
        fprintf(stderr, "couldnt connect\n");
        exit(EXIT_FAILURE);
    }
}

void server(void) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof addr;

    int connfd = accept(fd, (struct sockaddr *)&addr, &addrlen);
    if(connfd == -1) {
        fprintf(stderr, "couldnt accept connection\n");
        exit(EXIT_FAILURE);
    }

    if(bind(fd, (const struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
        fprintf(stderr, "couldnt bind\n");
        exit(EXIT_FAILURE);
    }

    while(true) {

    }
}
