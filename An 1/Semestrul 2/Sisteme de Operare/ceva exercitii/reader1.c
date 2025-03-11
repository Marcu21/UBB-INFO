#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    int fd;
    char * fifoPath = "/tmp/myfifo";

    // Crearea FIFO (dacă nu există deja)
    mkfifo(fifoPath, 0666);

    // Deschiderea FIFO pentru citire
    fd = open(fifoPath, O_RDONLY);
    int num;

    // Citirea numărului din FIFO
    read(fd, &num, sizeof(num));

    // Verificarea dacă numărul este par sau impar
    if (num % 2 == 0)
        printf("Procesul reader: Numarul %d este par.\n", num);
    else
        printf("Procesul reader: Numarul %d este impar.\n", num);

    // Închiderea FIFO
    close(fd);

    return 0;
}
