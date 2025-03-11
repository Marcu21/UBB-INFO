#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define MAX_SIZE 100

int main(int argc, char* argv[])
{
	char* fifo = "./fifo11realdada";
	int res = mkfifo(fifo, 0644);
	if(res==-1)
	{
		perror("mkfifo()");
		exit(EXIT_FAILURE);
	}
	char sir[MAX_SIZE];
	char vocale[] = "aeiouAEIOU";
	for(int i=0;i<strlen(vocale);i++)
	{
		int fdw = open(fifo, O_WRONLY);
		if(fdw==-1)
		{
			perror("open()");
			exit(EXIT_FAILURE);
		}
		write(fdw, &vocale[i], sizeof(char));
		close(fdw);
		int fdr = open(fifo, O_RDONLY);
        	if(fdr==-1)
        	{
                	perror("open()");
                	exit(EXIT_FAILURE);
        	}
        	read(fdr,sir,MAX_SIZE);
        	printf("Sirul este %s\n", sir);
        	close(fdr);
	}
}
