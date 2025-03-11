#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
int main(int argc,char* argv[])
{
		int p2c1[2];
		int res1 = pipe(p2c1);
		if(res1==-1)
		{
			perror("pipe()");
			exit(EXIT_FAILURE);
		}
		int c12p[2];
		int res2=pipe(c12p);
		if(res2==-1)
		{
			perror("pipe()");
			exit(EXIT_FAILURE);
		}
		int c22p[2];
		int res3=pipe(c22p);
		if(res3==-1)
		{
			perror("pipe()");
			exit(EXIT_FAILURE);
		}
		int p2c2[2];
		int res4=pipe(p2c2);
		if(res4==-1)
		{
			perror("pipe()");
			exit(EXIT_FAILURE);
		}
		int pid1 = fork();
		if(pid1==-1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}
		else if(pid1==0)
		{
			//din c1 scrii in parinte si din parinte citesti in c1
			close(c22p[0]);
			close(c22p[1]);
			close(p2c2[0]);
			close(p2c2[1]);
			close(c12p[0]);
			close(p2c1[1]);
			srandom(getpid());
			int n = rand()%1001;
			write(c12p[1], &n, sizeof(int));
			int semn;
			read(p2c1[0], &semn, sizeof(int));
			printf("Copil 1, numar %d, semn %d\n", n, semn);
			close(p2c1[0]);
			close(c12p[1]);
			exit(EXIT_SUCCESS);
		}
		int pid2=fork();
		if(pid2==-1)
		{
			perror("fork()");
			exit(EXIT_FAILURE);
		}
		else if(pid2==0)
		{
			close(c12p[0]);
			close(c12p[1]);
			close(p2c1[0]);
			close(p2c1[1]);
			close(c22p[0]);
			close(p2c2[1]);
			srandom(getpid());
			int n = rand()%1001;
			write(c22p[1], &n, sizeof(int));
			int semn;
			read(p2c2[0], &semn, sizeof(int));
			printf("Copil 2, numar %d, semn %d\n", n, semn);
			close(c22p[1]);
			close(p2c2[0]);
			exit(EXIT_SUCCESS);
		}
		//avem de scris din (p in c1 si c2) si de citit din (c1 in p si c2 in p)
		close(p2c1[0]);
		close(p2c2[0]);
		close(c12p[1]);
		close(c22p[1]);
		int n1, n2;
		read(c12p[0], &n1, sizeof(int));
		read(c22p[0],&n2, sizeof(int));
		int semn1, semn2;
		if(n1>n2)
		{
			semn1 = 1;
			semn2 = -1;
		}
		else if(n1<n2)
		{
			semn1 = -1;
			semn2 = 1;
		}
		else
		{
			semn1=0;
			semn2=0;
		}
		write(p2c1[1], &semn1, sizeof(int));
		write(p2c2[1], &semn2, sizeof(int));
		close(c12p[0]);
		close(c22p[0]);
		close(p2c1[1]);
		close(p2c2[1]);
		int status1, status2;
		wait(&status1);
		wait(&status2);
		exit(EXIT_SUCCESS);
}
