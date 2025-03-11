#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
 
int main() {
  int c;
  struct sockaddr_in server;
  uint16_t count;
  
  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(1234);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
  
  char sir[100], ch;
  printf("Introdu sirul: ");
  fgets(sir, sizeof(sir), stdin);
  sir[strlen(sir)-1] = '\0';
  printf("Introdu caracterul: ");
  scanf("%c", &ch);
  
  int len = strlen(sir);
  len = htons(len);
  
  send(c, &len, sizeof(len), 0);
  send(c, sir, ntohs(len)*sizeof(char), 0);
  send(c, &ch, sizeof(char), 0);
  
  recv(c, &count, sizeof(count), 0);
  count = ntohs(count);
  printf("Caracterul '%c' apare pe urmatoarele pozitii: ", ch);
  for (int i = 0; i < count; i++) {
        uint16_t pos;
        recv(c, &pos, sizeof(pos), 0);
        pos = ntohs(pos);
        printf("%d ", pos);
    }
    printf("\n");

  close(c);
}