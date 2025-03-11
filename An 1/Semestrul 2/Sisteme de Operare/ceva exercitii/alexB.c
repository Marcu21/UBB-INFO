#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE 100

int main(int argc, char* argv[])
{
	char *fifo = "./fifoalex";
	int fd = open(fifo, O_RDONLY);
	if(fd==-1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	char *tmp = malloc(sizeof(char)*MAX_SIZE);
	read(fd, tmp, MAX_SIZE);
	for(int i = 0;i<strlen(tmp);i++)
	{
		if(tmp[i]>='a' && tmp[i]<='z') tmp[i]=toupper(tmp[i]);
	}
	printf("Sirul este %s\n", tmp);
//	for(int i = 0;i<MAX_SIZE;i++) free(&tmp[i]);
	free(tmp);
	close(fd);
	exit(EXIT_SUCCESS);
}
