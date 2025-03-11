#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define MAX_SIZE 100

int main(int argc, char* argv[])
{
	char sir[MAX_SIZE] = "AlexandrauUE";
	int u = 0;
	while(u<10)
	{
		char* fifo = "./fifo11realdada";
		int fdr = open(fifo, O_RDONLY);
		if(fdr==-1)
		{
			perror("open()");
			exit(EXIT_FAILURE);
		}
		char voc;
		read(fdr,&voc,sizeof(char));
		close(fdr);
		int i=0;
		while(i<strlen(sir))
		{
			if(sir[i]==voc)
				for(int j=i;j<strlen(sir);j++) sir[j]=sir[j+1];
			else i++;
		}
		int fdw = open(fifo, O_WRONLY);
        	if(fdw==-1)
        	{
                	perror("open()");
                	exit(EXIT_FAILURE);
        	}
        	write(fdw, sir, MAX_SIZE);
        	close(fdw);
		u++;
	}
}
