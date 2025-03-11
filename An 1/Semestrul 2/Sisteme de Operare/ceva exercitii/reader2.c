#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#define MAX_BUF 1024

int main( int argc, char* argv[])
{
	char* fifo = "./fifo2";
	int fd = open(fifo, O_RDONLY);
	if ( fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	int num, ok = 1;
	read(fd, &num, sizeof(int));
	for(int i=2;i<=num/2;i++)
		if(num%i==0) ok = 0;
	if (ok == 1) printf("Numarul %d este prim\n", num);
	else printf("Numarul %d nu este prim\n", num);
	close(fd);
	return 0;
}
