#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
	int n = 20;
	int m = n;
	for(int i = 2;i<n;i++)
	{
		int nr,k=0;
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
			FILE* fd = fopen("numere.txt", "r");
			for(int j = 0;j<m;j++)
			{
				fscanf(fd, "%d", &nr);
				if(nr%i!=0 || i==nr)
				{
					write(pd[1], &nr, sizeof(int));
					k++;
				}
			}
			fclose(fd);
			m=k;
			close(pd[1]);
			exit(EXIT_SUCCESS);
		}
		else
		{
			wait(NULL);
			close(pd[1]);
			FILE* fd = fopen("numere.txt", "w");
			for(int j = 0;j<m;j++)
			{
				int num;
				read(pd[0], &num, sizeof(int));
				fprintf(fd, "%d ", num);
			}
			fclose(fd);
			close(pd[0]);
		}
	}
}
