#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#define MAX_BUF 1024

int main(int argc, char* argv[])
{
	char* fifo = "./fifo3";
	int fd = open(fifo, O_RDONLY);
	if ( fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	char c;
	char sir[MAX_BUF];
	read(fd, &c, sizeof(char));
	read(fd, sir, MAX_BUF);
	int frec = 0;
	for(int i = 0;i<strlen(sir);i++)
		if (sir[i]==c) frec++;
	printf("Frecventa caracterului %c este %d", c, frec);
	close(fd);
}
