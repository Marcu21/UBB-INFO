#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[])
{
	int fd[2];
	int res = pipe(fd);
	if (res == -1)
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
		int num;
		read(fd[0], &num, sizeof(int));
		int ok = 1;
		for( int i = 2; i<=num/2; i++)
			if ( num % i == 0) ok = 0;
		if ( ok == 0) printf("Numarul %d nu este prim\n", num);
		else printf("Numarul %d este prim\n", num);
		close(fd[0]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd[0]);
		printf("Introduceti un numar natural: ");
		int num;
		scanf("%d", &num);
		write(fd[1], &num, sizeof(int));
		close(fd[1]);
		int status;
		wait(&status);
	}
}
