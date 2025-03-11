#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char* argv[])
{
	char* fifo = "./fifo3";
	int res = mkfifo(fifo, 0644);
	if (res==-1)
	{
		perror("mkfifo()");
		exit(EXIT_FAILURE);
	}
	int fd = open(fifo, O_WRONLY);
	if (fd==-1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	char c;
	char sir[30];
	printf("Introdu un caracter: ");
	scanf("%c", &c);
	printf("Introdu un sir: ");
	scanf("%s", sir);
	write(fd, &c, sizeof(char));
	write(fd, sir, sizeof(char)*strlen(sir));
	close(fd);
	unlink(fifo);
	return 0;
}

