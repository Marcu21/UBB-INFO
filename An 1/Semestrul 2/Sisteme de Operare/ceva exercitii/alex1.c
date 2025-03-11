#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		printf("Utilizare incorecta! Nr argumente trb sa fie 1!\n");
		exit(EXIT_FAILURE);
	}
	int n = atoi(argv[1]);
	for(int i = 1;i<=n;i++)
	{
		int pid = fork();
		if(pid==-1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}
		else if (pid==0)
		{
			printf("Copil %d, pid: %d, parent pid: %d\n", i, getpid(), getppid());
			exit(EXIT_SUCCESS);
		}
		else
		{
			int status;
			wait(&status);
			//exit(EXIT_SUCCESS);
		}
	}
}
