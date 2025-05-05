#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define BUFFER_SIZE 1024

void error_exit(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void run_server() {
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) error_exit("socket");

    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = 0; // Let OS choose a free port

    if (bind(listen_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error_exit("bind");

    socklen_t addr_len = sizeof(serv_addr);
    if (getsockname(listen_fd, (struct sockaddr *)&serv_addr, &addr_len) < 0)
        error_exit("getsockname");

    char ip_str[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &serv_addr.sin_addr, ip_str, sizeof(ip_str));
    printf("Server listening on %s:%d\n", ip_str, ntohs(serv_addr.sin_port));

    if (listen(listen_fd, 1) < 0) error_exit("listen");

    int client_fd = accept(listen_fd, NULL, NULL);
    if (client_fd < 0) error_exit("accept");

    char buffer[BUFFER_SIZE];
    while (1) {
        ssize_t received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
        if (received <= 0) break;
        buffer[received] = '\0';
        printf("Received from client: %s\n", buffer);
        send(client_fd, "pong", 4, 0);
    }

    close(client_fd);
    close(listen_fd);
}

void run_client(const char *ip, int port) {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) error_exit("socket");

    struct sockaddr_in serv_addr = {0};
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0)
        error_exit("inet_pton");

    if (connect(sock_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error_exit("connect");

    char buffer[BUFFER_SIZE];
    while (1) {
        send(sock_fd, "ping", 4, 0);
        ssize_t received = recv(sock_fd, buffer, sizeof(buffer) - 1, 0);
        if (received <= 0) break;
        buffer[received] = '\0';
        printf("Received from server: %s\n", buffer);
        sleep(1);  // optional delay
    }

    close(sock_fd);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        run_server();
    } else if (argc == 3) {
        const char *ip = argv[1];
        int port = atoi(argv[2]);
        run_client(ip, port);
    } else {
        fprintf(stderr, "Usage: %s [ip port]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    return 0;
}
