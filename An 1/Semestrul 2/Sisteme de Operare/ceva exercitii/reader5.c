#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	char* fifo = "./fifo5";
	int fd = open(fifo, O_RDONLY);
	if(fd==-1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	int n, m, sum=0;
	read(fd, &n, sizeof(int));
	read(fd, &m, sizeof(int));
	sum = n+m;
	printf("SUMA: %d", sum);
	close(fd);
	return 0;
}
