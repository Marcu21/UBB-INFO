#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	while(1)
	{
		char* fifo = "./fifo__33__real";
		int fdr = open(fifo, O_RDONLY);
		if(fdr==-1)
		{
			perror("open()");
			exit(EXIT_FAILURE);
		}
		char ch;
		read(fdr, &ch, sizeof(char));
		FILE* fd = fopen("text.txt", "r");
		if (fd==NULL)
		{
			perror("fd()");
			exit(EXIT_FAILURE);
		}
		char litera;
		int frec = 0;
		while(fscanf(fd,"%c",&litera)>0)
			if(litera==ch) frec++;
		fclose(fd);
		close(fdr);
		int fdw = open(fifo, O_WRONLY);
		if(fdw==-1)
		{
			perror("open()");
			exit(EXIT_FAILURE);
		}
		write(fdw, &frec, sizeof(int));
		close(fdw);
		if(ch=='z') break;
	}
}
