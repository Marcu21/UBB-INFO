#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>

void deservire_client(int c) {
  // deservirea clientului
  uint16_t len;
  recv(c, &len, sizeof(len), MSG_WAITALL);
  len = ntohs(len);

  char sir[len + 1];
  recv(c, sir, len*sizeof(char), MSG_WAITALL);
  sir[len] = '\0';

  char ch;
  recv(c, &ch, sizeof(char), MSG_WAITALL);

  uint16_t pos[len], count = 0;
    for (int i = 0; i < len; i++)
    {
        if (sir[i] == ch)
        {
                pos[count++] = i;
        }
    }

  count = htons(count);
  send(c, &count, sizeof(count), 0);

  for (int i = 0; i < ntohs(count); i++)
  {
    uint16_t poz = htons(pos[i]);
    send(c, &poz, sizeof(poz), 0);
  }
  close(c);
  // sfarsitul deservirii clientului;
}

int main() {
  int s;
  struct sockaddr_in server, client;
  int c, l;

  s = socket(AF_INET, SOCK_STREAM, 0);
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

  listen(s, 5);

  l = sizeof(client);
  memset(&client, 0, sizeof(client));

  while (1) {
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client cu adresa ip %s\n", inet_ntoa(client.sin_addr));
    if (fork() == 0) { // fiu
      deservire_client(c);
      return 0;
    }
    // se executa doar in parinte pentru ca fiul se termina mai sus din cauza exit-ului
  }
}
