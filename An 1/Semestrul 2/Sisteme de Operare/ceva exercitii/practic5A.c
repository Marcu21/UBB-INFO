#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
	char *fifo = "./fifopractic5__";
	int res = mkfifo(fifo, 0644);
	if(res==-1)
	{
		perror("mkfifo()");
		exit(EXIT_FAILURE);
	}
	int x, nr;
	srandom(getpid());
	x = rand()%9001+1000;
	printf("Numarul care trebuie ghicit este %d\n", x);
	while(1)
	{
		int fdr = open(fifo, O_RDONLY);
        	if(fdr==-1)
        	{
                	perror("open()");
                	exit(EXIT_FAILURE);
        	}
		read(fdr, &nr, sizeof(int));
		char c;
		if(x>nr) c = '>';
		else if(x<nr) c = '<';
		else c = '=';
		close(fdr);
		int fdw = open(fifo, O_WRONLY);
		if(fdw==-1)
		{
			perror("open()");
			exit(EXIT_FAILURE);
		}
		write(fdw, &c, sizeof(char));
		close(fdw);
		if(c=='=') break;
	}
	unlink(fifo);
	exit(EXIT_SUCCESS);
}
