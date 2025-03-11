#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

int main(int agrc, char** argv)
{
	char vocale[] = "aeiouAEIOU";
	char sir[] = "Ana are mere";

	for(int i = 0; i < strlen(vocale); i++)
	{
		int pd[2];
		if(pipe(pd) < 0)
		{
			perror("pipe()");
			exit(0);
		}
		int pid = fork();
		if(pid == -1)
		{
			perror("fork()");
			exit(0);
		}
		if(pid == 0)
		{
			close(pd[0]);
			int frecventa = 0;
			for(int j = 0;j < strlen(sir); j++)
				if(sir[j] == vocale[i]) frecventa++;
			write(pd[1],&frecventa,sizeof(int));
			close(pd[1]);
			exit(0);
		}
		int n = 0;
		close(pd[1]);
		read(pd[0],&n,sizeof(int));
		close(pd[0]);
		printf("Litera: %c, frecventa: %d\n", vocale[i], n);
	}
	wait(NULL);
	return 0;
}
