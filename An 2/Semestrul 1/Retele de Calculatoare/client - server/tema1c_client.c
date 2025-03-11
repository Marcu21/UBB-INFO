#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdbool.h>

int main() {
  int c, l;
  struct sockaddr_in server;
  uint16_t nr;
  bool prim;

  c = socket(AF_INET, SOCK_DGRAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("172.23.1.158");

  printf("Introdu numarul: ");
  scanf("%hu", &nr);
  nr = htons(nr);

  sendto(c, &nr, sizeof(nr), 0, (struct sockaddr *) &server, sizeof(server));

  l = sizeof(server);
  recvfrom(c, &prim, sizeof(prim), 0, (struct sockaddr *) &server, &l);

  if(prim) printf("Numarul %hu este prim!\n", ntohs(nr));
  else printf("Numarul %hu NU este prim!\n", ntohs(nr));

  close(c);
}
