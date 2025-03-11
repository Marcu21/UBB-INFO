#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

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
		FILE *file = fopen("practic4.txt", "r");
		if(file==NULL)
		{
			perror("fopen()");
			exit(EXIT_FAILURE);
		}
		char c;
		int n;
		while(fscanf(file, "%c %d ", &c, &n)==2)
		{
			if(write(pd[1], &c, sizeof(char))==-1)
			{
				perror("write()");
				fclose(file);
				close(pd[1]);
				exit(EXIT_FAILURE);
			}
			if(write(pd[1], &n, sizeof(int))==-1)
			{
				perror("write()");
				fclose(file);
				close(pd[1]);
				exit(EXIT_FAILURE);
			}
		}
		fclose(file);
		close(pd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pd[1]);
		char c;
		int n;
		while(1)
		{
			if(read(pd[0], &c, sizeof(char))<=0) break;
			if(read(pd[0], &n, sizeof(int))<=0) break;
			if(c=='+')
			{
				int m = n,sum=0;
				while(m>0)
				{
					sum+=m%10;
					m/=10;
				}
				printf("%c %d %d\n", c, n, sum);
			}
			else if(c=='*')
			{
				int m = n,prod=1;
                                while(m>0)
                                {
                                        prod*=m%10;
                                        m/=10;
                                }
                                printf("%c %d %d\n", c, n, prod);
			}
		}
		close(pd[0]);
		exit(EXIT_SUCCESS);
	}
}
