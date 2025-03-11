#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#define MAX_SIZE 100

int main(int argc, char* argv[])
{
	FILE* fd = fopen("text.txt", "r");
	if (fd==NULL)
	{
		perror("fd()");
		exit(EXIT_FAILURE);
	}
	char *sir = malloc(sizeof(char)*MAX_SIZE);
	char* cuvant = malloc(sizeof(char)*MAX_SIZE);
	fscanf(fd, "%s", cuvant);
	strcpy(sir, cuvant);
	while(fscanf(fd,"%s",cuvant)>0) strcat(sir, cuvant);
	for(char ch='a';ch<='z';ch++)
	{
		int pd[2];
		int res = pipe(pd);
		if(res==-1)
		{
			perror("pipee()");
			exit(EXIT_FAILURE);
		}
		int pid = fork();
		if(pid==-1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}
		else if(pid==0)
		{
			close(pd[0]);
			int frec = 0;
			for(int i = 0;i<strlen(sir);i++)
				if(sir[i]==ch) frec++;
			write(pd[1], &ch, sizeof(char));
			write(pd[1], &frec, sizeof(int));
			close(pd[1]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(NULL);
			close(pd[1]);
			int frec;
			char ch;
			read(pd[0], &ch, sizeof(char));
			read(pd[0], &frec, sizeof(int));
			printf("Frecventa aparitiei caracterului %c este %d\n", ch, frec);
			close(pd[0]);
//			exit(EXIT_SUCCESS);
		}
	}
	free(sir);
	free(cuvant);
}
