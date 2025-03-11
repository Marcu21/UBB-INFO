#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

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
		FILE *file = fopen("operatii.txt", "r");
		if(file==NULL)
		{
			perror("fopen()");
			exit(EXIT_FAILURE);
		}
		char semn;
		int n, m;
		while(fscanf(file, "%c %d %d ", &semn, &n, &m)==3)
		{
			write(pd[1], &semn, sizeof(char));
			write(pd[1], &n, sizeof(int));
			write(pd[1], &m, sizeof(int));
		}
		close(pd[1]);
		fclose(file);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pd[1]);
		int status;
		wait(&status);
		while(1)
		{
			char semn;
			int n,m;
			if(read(pd[0], &semn, sizeof(char))<=0) break;
			read(pd[0], &n,sizeof(int));
			read(pd[0], &m, sizeof(int));
			if(semn=='+')
			{
				int sum = n+m;
				printf("%d + %d = %d\n", n, m, sum);
			}
			else if(semn=='-')
			{
				int dif = n - m;
				printf("%d - %d = %d\n", n, m , dif);
			}
			else printf("hatz gion");
		}
		close(pd[0]);
		exit(EXIT_SUCCESS);
	}
}
	
