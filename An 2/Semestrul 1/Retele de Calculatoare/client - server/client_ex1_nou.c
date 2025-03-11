#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#define MAX_MSG_LEN 1024
#define SERVER_IP "127.0.0.1"  // Adresa IP a serverului
#define SERVER_PORT 1234        // Portul TCP al serverului

int main() {
    int tcp_sock, udp_sock;
    struct sockaddr_in server_addr, udp_addr;
    char buffer[MAX_MSG_LEN];
    int port;

    // Solicitarea portului UDP de la utilizator
    printf("Introdu portul UDP: ");
    scanf("%d", &port);
    getchar(); // Consumăm newline-ul rămas după scanf

    // Creare socket TCP
    tcp_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_sock < 0) {
        perror("Eroare la crearea socketului TCP");
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // Conectare la serverul TCP
    if (connect(tcp_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Eroare la conectare TCP");
        close(tcp_sock);
        return 1;
    }

    // Trimite serverului numărul de port UDP
    if (send(tcp_sock, &port, sizeof(port), 0) < 0) {
        perror("Eroare la trimiterea portului UDP");
        close(tcp_sock);
        return 1;
    }

    // Creare socket UDP
    udp_sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (udp_sock < 0) {
        perror("Eroare la crearea socketului UDP");
        close(tcp_sock);
        return 1;
    }

    memset(&udp_addr, 0, sizeof(udp_addr));
    udp_addr.sin_family = AF_INET;
    udp_addr.sin_port = htons(port);
    udp_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind pe socketul UDP
    if (bind(udp_sock, (struct sockaddr *)&udp_addr, sizeof(udp_addr)) < 0) {
        perror("Eroare la bind UDP");
        close(udp_sock);
        close(tcp_sock);
        return 1;
    }

    // Începe să primești și să trimiți mesaje
    struct sockaddr_in from_addr;
    socklen_t from_len = sizeof(from_addr);
    while (1) {
        printf("Introdu mesajul (scrie 'by' pentru a închide): ");
        fgets(buffer, MAX_MSG_LEN, stdin);
        if (strcmp(buffer, "by\n") == 0) {
            send(tcp_sock, "by", 3, 0); // Include NULL terminator
            break;
        }

        // Trimitere mesaj prin TCP pentru a fi redirecționat de server
        if (send(tcp_sock, buffer, strlen(buffer) + 1, 0) < 0) {
            perror("Eroare la trimiterea mesajului");
            continue;
        }

        // Așteaptă mesaje de la server prin UDP
        memset(buffer, 0, MAX_MSG_LEN);
        if (recvfrom(udp_sock, buffer, MAX_MSG_LEN, 0, (struct sockaddr *)&from_addr, &from_len) > 0) {
            printf("Mesaj pentru %s de la %s\n", inet_ntoa(from_addr.sin_addr), buffer);
        }
    }

    close(udp_sock);
    close(tcp_sock);
    return 0;
}
