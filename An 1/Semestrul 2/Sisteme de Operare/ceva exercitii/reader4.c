#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX_BUF 1024

int main(int argc, char* argv[])
{
	char* fifo = "./fifo4";
	int fd = open(fifo, O_RDONLY);
	if (fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	int n, m;
	read(fd, &n, sizeof(int));
	read(fd, &m, sizeof(int));
	int sum = n+m;
	printf("Suma: %d", sum);
	close(fd);
	return 0;
}
