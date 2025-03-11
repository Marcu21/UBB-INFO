#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	char* fifo = "./fifo4";
	int res = mkfifo(fifo, 0644);
	if (res == -1)
	{
		perror("mkfifo()");
		exit(EXIT_FAILURE);
	}
	int fd = open(fifo, O_WRONLY);
	if ( fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	printf("Introdu un numar: ");
	int n,m;
	scanf("%d", &n);
	printf("Introdu al doilea numar: ");
	scanf("%d", &m);
	write(fd, &n, sizeof(int));
	write(fd, &m, sizeof(int));
	close(fd);
	unlink(fifo);
	return 0;
}
