#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_SIZE 100

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		printf("Utilizare incorecta!");
		exit(EXIT_FAILURE);
	}
	char* fifo = "./fifoalex";
	int res = mkfifo(fifo, 0644);
	if(res==-1)
	{
		perror("mkfifo()");
		exit(EXIT_FAILURE);
	}
	int fd = open(fifo, O_WRONLY);
	if(fd==-1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	write(fd, argv[1], MAX_SIZE);
	close(fd);
	unlink(fifo);
	exit(EXIT_SUCCESS);
}
