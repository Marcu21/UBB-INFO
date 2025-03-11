#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_SIZE 100

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		perror("Utilizare incorecta!");
		exit(EXIT_FAILURE);
	}
	char sir[strlen(argv[1])+1];
	strcpy(sir, argv[1]);
	char vocale[]="aeiouAEIOU";
	for(int i=0;i<strlen(vocale);i++)
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
			char *tmp;
			tmp = malloc(MAX_SIZE*sizeof(char));
			int k = -1;
			for(int j =0;j<strlen(sir);j++)
			{
				if(sir[j]!=vocale[i]) tmp[++k]=sir[j];
			}
			tmp[++k]='\n';
			write(pd[1],tmp,MAX_SIZE);
			free(tmp);
			exit(EXIT_SUCCESS);
		}
		else
		{
			close(pd[1]);
			char *tmp = malloc(MAX_SIZE*sizeof(char));
			read(pd[0],tmp,MAX_SIZE);
			strcpy(sir,tmp);
			free(tmp);
			wait(NULL);

		}
	}
	printf("SIRUL ESTE: %s", sir);
}
