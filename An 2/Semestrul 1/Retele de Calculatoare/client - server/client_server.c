#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 1234

uint16_t my_htons(uint16_t hostshort) {
    return (hostshort >> 8) | (hostshort << 8);
}


uint16_t my_ntohs(uint16_t netshort) {
    return my_htons(netshort);
}

int main() {
    int tcp_sock, udp_sock;
    struct sockaddr_in server_addr, udp_addr, partner_addr;
    uint16_t port, port_net, local_num, received_num, local_num_net;
    char buffer[1024];

    printf("Introdu portul UDP: ");
    scanf("%hu", &port);
    getchar();

    tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_sock < 0) {
        perror("Eroare la crearea socketului TCP");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if (connect(tcp_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Eroare la conectare TCP");
        close(tcp_sock);
        return 1;
    }

    port_net = my_htons(port);
    if (send(tcp_sock, &port_net, sizeof(port_net), 0) < 0) {
        perror("Eroare la trimiterea portului UDP");
        close(tcp_sock);
        return 1;
    }

    if (recv(tcp_sock, buffer, sizeof(buffer), 0) <= 0) {
        perror("Eroare la primirea informatiilor partenerului");
        close(tcp_sock);
        return 1;
    }
    close(tcp_sock);

    char partner_ip[INET_ADDRSTRLEN];
    uint16_t partner_port;
    sscanf(buffer, "%s %hu", partner_ip, &partner_port);
    //partner_port = ntohs(partner_port);
    printf("IP partener: %s, Port UDP partener: %hu\n", partner_ip, partner_port);


    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock < 0) {
        perror("Eroare la crearea socketului UDP");
        return 1;
    }

    memset(&udp_addr, 0, sizeof(udp_addr));
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(port);
    udp_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(udp_sock, (struct sockaddr *)&udp_addr, sizeof(udp_addr)) < 0) {
        perror("Eroare la bind UDP");
        close(udp_sock);
        return 1;
    }

    memset(&partner_addr, 0, sizeof(partner_addr));
    partner_addr.sin_family = AF_INET;
    partner_addr.sin_port = my_htons(partner_port);
    partner_addr.sin_addr.s_addr = inet_addr(partner_ip);

    do {
        printf("Introduceti un numar: ");
        scanf("%hu", &local_num);
        local_num_net = my_htons(local_num);
        sendto(udp_sock, &local_num_net, sizeof(local_num_net), 0, (struct sockaddr *)&partner_addr, sizeof(partner_addr));
        socklen_t addr_len = sizeof(partner_addr);
        recvfrom(udp_sock, &received_num, sizeof(received_num), 0, (struct sockaddr *)&partner_addr, &addr_len);
        received_num = my_ntohs(received_num);

        printf("Numar primit: %hu\n", received_num);
    } while (local_num != received_num);

    close(udp_sock);
    return 0;
}