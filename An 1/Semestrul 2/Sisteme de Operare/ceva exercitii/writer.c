//
// writer.c
//
// Using named pipe (FIFO) - Create and write to a FIFO
//

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
    // set the FIFO path
    char* fifo = "./fifo";

    // create the FIFO (named pipe)
    int res = mkfifo(fifo, 0644);
    if (res == -1)
    {
        perror("mkfifo()");
        exit(EXIT_FAILURE);
    }

    // open the FIFO for write
    int fd = open(fifo, O_WRONLY);
    if (fd == -1)
    {
        perror("open()");
        exit(EXIT_FAILURE);
    }

    // write a string to the FIFO
    char msg[] = "Hello from FIFO";
    write(fd, msg, sizeof(msg));

    // close the FIFO
    close(fd);

    // remove the FIFO
    unlink(fifo);

    return 0;
}
