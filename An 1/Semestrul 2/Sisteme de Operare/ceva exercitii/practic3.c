#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#define MAX_SIZE 100

int main(int argc, char* argv[])
{
	int pd[2];
	int res = pipe(pd);
	if(res==-1)
	{
		perror("pipe()");
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
		FILE *file = fopen("practic3.txt", "r");
		if(file==NULL)
		{
			perror("fopen()");
			exit(EXIT_FAILURE);
		}
		char litera;
		char *sir = malloc(sizeof(char)*MAX_SIZE);
		while(fscanf(file, "%c %s ", &litera, sir)==2)
		{
			write(pd[1], &litera, sizeof(char));
			write(pd[1], sir, MAX_SIZE);
		}
		free(sir);
		fclose(file);
		close(pd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pd[1]);
		int status;
		wait(&status);
		char c;
                char *sir = malloc(sizeof(char)*MAX_SIZE);
		while(1)
		{
			if(read(pd[0], &c, sizeof(char))<=0) break;
			if(read(pd[0], sir, MAX_SIZE)<=0) break;
			int poz = -1;
			for(int i=0;i<strlen(sir)&&poz==-1;i++)
				if(sir[i]==c) poz=i;
			printf("%c %s %d\n", c, sir, poz);
		}
		free(sir);
		close(pd[1]);
		exit(EXIT_SUCCESS);
	}
}
