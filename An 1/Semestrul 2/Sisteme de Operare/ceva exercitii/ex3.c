#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_SIZE 100

int main(int argc, char* argv[])
{
	int fd[2];
	int res = pipe(fd);
	if(res==-1)
	{
		perror("pipe(fd)");
		exit(EXIT_FAILURE);
	}
	int pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		close(fd[1]);
		char c;
		char sir[MAX_SIZE];
		read(fd[0], &c, sizeof(char));
		read(fd[0], sir, MAX_SIZE);
		int nr = 0;
		for(int i=0;i<strlen(sir);i++)
		{
			if(sir[i]==c) nr++;
		}
		printf("Numarul de aparitii al caracterului %c in sir este %d\n", c, nr);
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[0]);
		printf("Introdu un caracter: ");
		char c;
		scanf("%c", &c);
		char sir[MAX_SIZE];
		printf("Introdu sirul: ");
		scanf("%s", sir);
		write(fd[1], &c, sizeof(char));
		write(fd[1], sir, MAX_SIZE);
		close(fd[1]);
		int status;
		wait(&status);
	}
}
