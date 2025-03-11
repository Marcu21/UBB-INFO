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
	int minn=1000, maxx=10000;
	while(1)
	{
		int nr = (maxx+minn)/2;
		int fdw = open(fifo, O_WRONLY);
                if(fdw==-1)
                {
                        perror("open()");
                        exit(EXIT_FAILURE);
                }
		write(fdw, &nr, sizeof(int));
		close(fdw);
		int fdr = open(fifo, O_RDONLY);
                if(fdr==-1)
                {
                        perror("open()");
                        exit(EXIT_FAILURE);
                }
		char semn;
		read(fdr, &semn, sizeof(char));
		printf("B trimite lui A %d, iar A trimite inapoi lui B semnul %c\n", nr, semn);
		if(semn=='<') maxx=nr-1;
		else if(semn=='>') minn=nr+1;
		else break;
		close(fdr);
	}
	exit(EXIT_SUCCESS);
}
