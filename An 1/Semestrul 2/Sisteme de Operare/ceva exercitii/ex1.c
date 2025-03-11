#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h> // Include this header for wait()

int main(int argc, char* argv[])
{
    // creez pipe ul
        int pd[2];
        int res = pipe(pd);
        if (res == -1)                      // fork() failed
    {
        perror("pipe() error: ");
        exit(EXIT_FAILURE);
    }

        //creez copil
    int pid = fork();
    if (pid == -1)                      // fork() failed
    {
        perror("fork() error: ");
        exit(EXIT_FAILURE);
    }

    if (pid == 0)                       // in child
    {
                close(pd[1]); // Închide capătul de scriere

        int num;
        read(pd[0], &num, sizeof(num));
        close(pd[0]); // Închide capătul de citire

        if (num % 2 == 0)
            printf("Procesul copil: Numarul %d este par.\n", num);
        else
            printf("Procesul copil: Numarul %d este impar.\n", num);
        exit(EXIT_SUCCESS);
    }
    else                                // in parent
    {
                close(pd[0]); //inchid capatul de citire
                int num;
        printf("Introduceti un numar natural: ");
        scanf("%d", &num);

        write(pd[1], &num, sizeof(num));
        close(pd[1]); // Închide capătul de scriere
	int status;
	wait(&status);
    }
}
