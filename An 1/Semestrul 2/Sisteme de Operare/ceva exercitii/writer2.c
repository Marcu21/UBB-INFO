#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int main(int argc, char* argv[])
{
	char* fifo = "./fifo2";
	int res = mkfifo(fifo, 0644);
	if (res == -1)
	{
		perror("mkfifo()");
		exit(EXIT_FAILURE);
	}
	int fd = open(fifo, O_WRONLY);
	if (fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	printf("Introduceti un numar natural: ");
	int num;
	scanf("%d", &num);
	write(fd, &num, sizeof(int));
	close(fd);
	unlink(fifo);
	return 0;
}
