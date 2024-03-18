// https://csperkins.org/teaching/2007-2008/networked-systems/lecture04.pdf
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

const char example[] = {0xD, 0xE, 0xA, 0xD, 0xB, 0xE, 0xE, 0xF};

void client() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        fprintf(stderr, "couldnt create socket (%d)\n", errno);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);

    if(connect(fd, (struct sockaddr *)&addr, sizeof addr) == -1) {
        fprintf(stderr, "couldnt connect\n");
        exit(EXIT_FAILURE);
    }

    char expected[sizeof example];
    if(read(fd, expected, sizeof example) == -1) {
        fprintf(stderr, "couldnt read\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < sizeof example; i++) {
        printf("%X", expected[i]);
    }
    printf("\n");

    close(fd);
}

void server(void) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == -1) {
        fprintf(stderr, "couldnt create socket (%d)\n", errno);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(5000);
    socklen_t addrlen = sizeof addr;

    if(bind(fd, (const struct sockaddr *)&addr, sizeof(struct sockaddr)) == -1) {
        fprintf(stderr, "couldnt bind\n");
        exit(EXIT_FAILURE);
    }

    listen(fd, 2);

    while(true) {
        int connfd = accept(fd, (struct sockaddr *)&addr, &addrlen);
        if(connfd == -1) {
            fprintf(stderr, "couldnt accept connection\n");
            exit(EXIT_FAILURE);
        }

        write(connfd, example, sizeof example);

        close(connfd);
        sleep(1);
    }

    close(fd);
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("supply either \"client\" or \"server\"\n");
        return 0;
    }

    if(strcmp(argv[1], "client") == 0)
        client();
    else if(strcmp(argv[1], "server") == 0)
        server();

    return 0;
}
