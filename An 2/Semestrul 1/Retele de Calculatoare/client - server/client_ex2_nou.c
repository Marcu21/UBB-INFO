#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server;
    int numbers[100];  // Mărimea maximă a șirului de numere
    int count = 0;
    int lcm;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Eroare la crearea socketului");
        return 1;
    }

    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_port = htons(1234);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0) {
        perror("Eroare la conectare");
        return 1;
    }

    printf("Introdu numarul de numere: ");
    scanf("%d", &count);
    printf("Introdu numerele: ");
    for(int i = 0; i < count; i++) {
        scanf("%d", &numbers[i]);
    }

    // Trimitem numărul de elemente și apoi numerele
    send(sock, &count, sizeof(count), 0);
    send(sock, numbers, sizeof(int) * count, 0);
    
    // Primim CMMMC
    recv(sock, &lcm, sizeof(lcm), 0);
    lcm = ntohl(lcm); // Convertim din network byte order în host byte order
    printf("Cel mai mic multiplu comun primit este: %d\n", lcm);
    
    close(sock);
    return 0;
}
