#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	int nr = 20;
	while(1)
	{
		char* fifo = "./fifo__22";
		int fdr = open(fifo, O_RDONLY);
		if(fdr==-1)
		{
			perror("open()");
			exit(EXIT_FAILURE);
		}
		int i;	
		read(fdr, &i, sizeof(int));
		close(fdr);
		FILE* fd = fopen("numere.txt", "r");
		if (fd==NULL)
		{
			perror("fd()");
			exit(EXIT_FAILURE);
		}
		int *tmp = malloc(sizeof(int)*nr);
		int k = -1, nrnou=0;
		for(int j = 0;j<nr;j++)
		{
			int num;
			fscanf(fd,"%d",&num);
			if(num%i==1 || num==i) 
			{
				tmp[++k]=num;
				nrnou++;
			}
		}
		fclose(fd);
		FILE* fdnou = fopen("numere.txt", "w");
		if (fdnou==NULL)
		{
			perror("fopen()");
			exit(EXIT_FAILURE);
		}
		for(int j=0;j<nrnou;j++)
			fprintf(fdnou,"%d ",tmp[j]);
		fclose(fdnou);
		nr=nrnou;
		for(int j=0;j<nr;j++) free(&tmp[j]);
		//free(tmp);
	}
}
