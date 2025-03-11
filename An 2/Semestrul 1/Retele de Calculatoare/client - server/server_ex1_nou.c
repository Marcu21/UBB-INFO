#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CLIENTS 100
#define BUF_SIZE 1024

typedef struct {
    struct sockaddr_in addr;
    int active;
} Client;

Client clients[MAX_CLIENTS];
int udp_sock;
pthread_mutex_t lock;

void *client_handler(void *arg) {
    int sock = *(int *)arg;
    free(arg);
    int port;
    char buffer[BUF_SIZE];
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr);

    if (recv(sock, &port, sizeof(port), 0) <= 0) {
        perror("Failed to receive UDP port");
        close(sock);
        return NULL;
    }

    if (getpeername(sock, (struct sockaddr *)&client_addr, &len) == -1) {
        perror("Failed to get client address");
        close(sock);
        return NULL;
    }

    client_addr.sin_port = htons(port);  // Set the UDP port received from the client

    pthread_mutex_lock(&lock);
    int index = -1;
    for (int i = 0; i < MAX_CLIENTS; i++) {
        if (!clients[i].active) {
            clients[i].addr = client_addr;
            clients[i].active = 1;
            index = i;
            break;
        }
    }
    pthread_mutex_unlock(&lock);

    if (index == -1) {
        fprintf(stderr, "Server full.\n");
        close(sock);
        return NULL;
    }

    while ((recv(sock, buffer, BUF_SIZE, 0)) > 0) {
        if (strcmp(buffer, "by") == 0) {
            break;
        }
        char msg[BUF_SIZE];
        snprintf(msg, BUF_SIZE, "%s: %s", inet_ntoa(client_addr.sin_addr), buffer);

        pthread_mutex_lock(&lock);
        for (int i = 0; i < MAX_CLIENTS; i++) {
            if (i != index && clients[i].active) {
                sendto(udp_sock, msg, strlen(msg) + 1, 0, 
                       (struct sockaddr *)&clients[i].addr, sizeof(clients[i].addr));
            }
        }
        pthread_mutex_unlock(&lock);
    }

    pthread_mutex_lock(&lock);
    clients[index].active = 0;
    pthread_mutex_unlock(&lock);
    close(sock);
    return NULL;
}

int main() {
    int tcp_sock, *new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    pthread_t tid;

    tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_sock < 0) {
        perror("Failed to create TCP socket");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(1234);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(tcp_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Failed to bind TCP socket");
        return 1;
    }

    listen(tcp_sock, MAX_CLIENTS);
    printf("TCP server ready for connections...\n");

    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock < 0) {
        perror("Failed to create UDP socket");
        return 1;
    }

    memset(clients, 0, sizeof(clients));
    pthread_mutex_init(&lock, NULL);

    while (1) {
        new_sock = malloc(sizeof(int));
        *new_sock = accept(tcp_sock, (struct sockaddr *)&client_addr, &addr_size);
        if (*new_sock < 0) {
            perror("Failed to accept connection");
            free(new_sock);
            continue;
        }
        pthread_create(&tid, NULL, client_handler, new_sock);
    }

    close(tcp_sock);
    close(udp_sock);
    pthread_mutex_destroy(&lock);
    return 0;
}
