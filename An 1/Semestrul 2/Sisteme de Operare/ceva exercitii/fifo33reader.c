#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char* argv[])
{
	char* fifo = "./fifo_____33";
        int fd = open(fifo, O_RDONLY);
        if(fd==-1)
        {
                 perror("open()");
                 exit(EXIT_FAILURE);
        }
	for(char c='a';c<='z';c++)
	{
		char ch;
		int frec;
		read(fd, &ch, sizeof(char));
		read(fd, &frec, sizeof(int));
		printf("Frecventa caracterului %c este %d\n", ch, frec);
		close(fd);
		return 0;
	}
}
