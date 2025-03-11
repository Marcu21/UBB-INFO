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
	else if(pid == 0)
	{
		close(pd[0]);
		int i = 1;
		while(1)
		{
			printf("Introdu un numar natural: ");
			int k;
			scanf("%d", &k);
			srandom(i);
			int n = rand();
			write(pd[1], &k, sizeof(int));
			write(pd[1], &n, sizeof(int));
			i++;
			if(k==0) break;
		}
		close(pd[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pd[1]);
		FILE *file = fopen("fisier.txt", "w");
		if(file==NULL)
		{
			perror("fopen()");
			exit(EXIT_FAILURE);
		}
		while(1)
		{
			int k, n;
			read(pd[0], &k, sizeof(int));
			read(pd[0], &n, sizeof(int));
			if(k%2==0)
			{
				int m = n, sum=0;
				while(m>0)
				{
					sum=sum+m%10;
					m=m/10;
				}
				fprintf(file, "%d ", k);
				fprintf(file, "%d ", n);
				fprintf(file, "%d ", sum);
			}
			else
			{
				int m=n,inm=1;
				while(m>0)
                                {
                                        inm=inm*m%10;
                                        m=m/10;
                                }
                                fprintf(file, "%d ", k);
                                fprintf(file, "%d ", n);
                                fprintf(file, "%d ", inm);
			}
			if(k==0) break;
		}
		fclose(file);
		close(pd[0]);
	}
}
