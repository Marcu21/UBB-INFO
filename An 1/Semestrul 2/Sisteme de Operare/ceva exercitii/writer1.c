#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    int fd;
    char * fifoPath = "/tmp/myfifo";

    // Crearea FIFO
    mkfifo(fifoPath, 0666);

    // Deschiderea FIFO pentru scriere
    fd = open(fifoPath, O_WRONLY);
    int num;
    printf("Introduceti un numar natural: ");
    scanf("%d", &num);

    // Scrierea numărului în FIFO
    write(fd, &num, sizeof(num));

    // Închiderea FIFO
    close(fd);

    // Ștergerea FIFO
    unlink(fifoPath);

    return 0;
}
