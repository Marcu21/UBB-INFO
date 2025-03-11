#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	char* fifo = "./fifo5";
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
	FILE *file = fopen("numere.txt", "r");
	if(file==NULL)
	{
		perror("fopen()");
		exit(EXIT_FAILURE);
	}
	int n, m;
	if(fscanf(file,"%d %d", &n, &m)!=2)
	{
		perror("fscanf()");
		fclose(file);
		exit(EXIT_FAILURE);
	}
	write(fd, &n, sizeof(int));
	write(fd, &m, sizeof(int));
	close(fd);
	fclose(file);
	unlink(fifo);
	return 0;
}
