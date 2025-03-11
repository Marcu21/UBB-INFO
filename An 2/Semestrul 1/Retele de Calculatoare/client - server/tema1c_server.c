#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdbool.h>

bool e_prim(uint16_t nr)
{
	if(nr <= 1) return false;
	if(nr % 2 == 0 && nr > 2) return false;
	for(uint16_t i = 3; i * i <= nr; i += 2)
		if(nr % i == 0) return false;
	return true;
}

int main() {
  int s;
  struct sockaddr_in server, client;
  int c, l;
  uint16_t nr;
  bool prim;

  s = socket(AF_INET, SOCK_DGRAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;

  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }

  l = sizeof(client);
  memset(&client, 0, sizeof(client));

  recvfrom(s, &nr, sizeof(nr), MSG_WAITALL, (struct sockaddr *) &client, &l);
  nr = ntohs(nr);
  prim = e_prim(nr);
  sendto(s, &prim, sizeof(prim), 0, (struct sockaddr *) &client, l);


  close(s);
}
