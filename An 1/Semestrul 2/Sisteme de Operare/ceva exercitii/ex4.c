#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main( int argc, char* argv[])
{
	int p2c[2];
	int res = pipe(p2c);
	if(res == -1)
	{
		perror("pipe(p2c)");
		exit(EXIT_FAILURE);
	}
	int c2p[2];
	int res2 = pipe(c2p);
	if(res2 == -1)
	{
		perror("pipe(c2p)");
		exit(EXIT_FAILURE);
	}
	int pid = fork();
	if (pid == -1)
	{
		perror("fork()");
		exit(EXIT_FAILURE);
	}
	else if( pid == 0)
	{
		close(p2c[1]);
		close(c2p[0]);
		int n, m;
		read(p2c[0], &n, sizeof(int));
		read(p2c[0], &m, sizeof(int));
		int sum = n + m;
		write(c2p[1], &sum, sizeof(int));
		close(p2c[0]);
		close(c2p[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(p2c[0]);
		close(c2p[1]);
		printf("Introdu primul numar: ");
		int n, m;
		scanf("%d", &n);
		printf("Introdu al doilea numar: ");
		scanf("%d", &m);
		write(p2c[1], &n, sizeof(int));
		write(p2c[1], &m, sizeof(int));
		int status;
		wait(&status);
		int sum;
		read(c2p[0], &sum, sizeof(int));
		printf("Suma lui %d si %d este %d\n", n, m, sum);
		close(p2c[1]);
		close(c2p[0]);
	}
}
