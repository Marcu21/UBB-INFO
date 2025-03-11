#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
	char* fifo = "./fifo__22";
	int res = mkfifo(fifo, 0644);
	if(res==-1)
	{
		perror("mkfifo()");
		exit(EXIT_FAILURE);
	}
	int n = 20;
	for(int i = 2; i < n; i++)
	{
		int fdw = open(fifo, O_WRONLY);
		if(fdw==-1)
		{
			perror("open()");
			exit(EXIT_FAILURE);
		}
		write(fdw, &i, sizeof(int));
		close(fdw);
	}
}
