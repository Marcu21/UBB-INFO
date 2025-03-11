#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdint.h>

#define MAX_CLIENTS 2
#define BUFFER_SIZE 1024

typedef struct {
    struct sockaddr_in address;
    int sockfd;
    int udp_port;
} client_data;

client_data clients[MAX_CLIENTS];
int num_clients = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

uint16_t my_htons(uint16_t hostshort) {
    return (hostshort >> 8) | (hostshort << 8);
}


uint16_t my_ntohs(uint16_t netshort) {
    return my_htons(netshort);
}

void *client_handler(void *arg) {
    int idx = *(int*)arg;
    free(arg);

    client_data *client = &clients[idx];
    char buffer[BUFFER_SIZE];

    if (recv(client->sockfd, buffer, BUFFER_SIZE, 0) > 0) {
        client->udp_port = my_ntohs(*(uint16_t*)buffer);
        printf("Received UDP port %hu from client %s\n", client->udp_port, inet_ntoa(client->address.sin_addr));
    }
    pthread_mutex_lock(&lock);
    num_clients++;
    pthread_mutex_unlock(&lock);
    if (num_clients == 2) {
        printf("S au conectat 2 clienti\n");
        for (int i = 0; i < 2; i++) {
            client_data *other = &clients[1 - i];
            snprintf(buffer, BUFFER_SIZE, "%s %hu", inet_ntoa(other->address.sin_addr), other->udp_port);
            send(clients[i].sockfd, buffer, strlen(buffer), 0);
            close(clients[i].sockfd);
        }
        num_clients = 0;
    }

    return NULL;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = my_htons(1234);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    listen(server_fd, 3);

    printf("Server listening on port 1234...\n");

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0) {
            perror("accept");
            continue;
        }

        int *idx = malloc(sizeof(int));
        *idx = num_clients;

        clients[num_clients].sockfd = new_socket;
        clients[num_clients].address = address;

        pthread_t tid;
        if(pthread_create(&tid, NULL, client_handler, idx) != 0) {
            perror("Failed to create thread");
        }
        pthread_detach(tid);
    }

    return 0;
}