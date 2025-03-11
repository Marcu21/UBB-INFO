#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    char* fifo = "./fifo__33__real";
    int res = mkfifo(fifo, 0644);
    if(res==-1)
    {
        perror("mkfifo()");
        exit(EXIT_FAILURE);
    }
    for(char ch='a';ch<='z';ch++)
    {
	int fdw = open(fifo, O_WRONLY);
	if(fdw==-1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	write(fdw, &ch, sizeof(char));
	close(fdw);
	int fdr = open(fifo, O_RDONLY);
	if(fdr==-1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	int frec;
	read(fdr, &frec, sizeof(int));
	printf("Caracterul %c are frecventa %d\n", ch, frec);
	close(fdr);
    }
}
