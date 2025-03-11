#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#define MAX_SIZE 1000  // Increased size for buffer to handle the concatenation properly

int main(int argc, char* argv[])
{
    FILE* fd = fopen("text.txt", "r");
    if (fd == NULL)
    {
        perror("fd()");
        exit(EXIT_FAILURE);
    }
    char *sir = malloc(sizeof(char) * MAX_SIZE);
    if (sir == NULL) {
        perror("malloc sir failed");
        exit(EXIT_FAILURE);
    }
    char *cuvant = malloc(sizeof(char) * MAX_SIZE);
    if (cuvant == NULL) {
        perror("malloc cuvant failed");
        exit(EXIT_FAILURE);
    }
    sir[0] = '\0';  // Start with an empty string

    // Read words and concatenate them into 'sir'
    while (fscanf(fd, "%s", cuvant) != EOF) {
        strcat(sir, cuvant);
        strcat(sir, " ");  // Add space to separate words
    }
    fclose(fd);

    for (char ch = 'a'; ch <= 'z'; ch++) {
        char input_fifo[30];
        sprintf(input_fifo, "./input_fifo%c", ch);  // Unique FIFO for each character

        if (mkfifo(input_fifo, 0644) == -1) {
            perror("mkfifo()");
            exit(EXIT_FAILURE);
        }

        int pid = fork();
        if (pid == -1) {
            perror("fork()");
            exit(EXIT_FAILURE);
        } else if (pid == 0) {
            // Child process
            int pd = open(input_fifo, O_WRONLY);
            int frec = 0;
            for (int i = 0; i < strlen(sir); i++) {
                if (sir[i] == ch) frec++;
            }
            write(pd, &frec, sizeof(int));  // Only write the frequency, not the character
            close(pd);
            exit(EXIT_SUCCESS);
        } else {
            // Parent process
            wait(NULL);
            int pd = open(input_fifo, O_RDONLY);
            int frec;
            read(pd, &frec, sizeof(int));  // Read only the frequency
            printf("Frecventa aparitiei caracterului %c este %d\n", ch, frec);
            close(pd);
            unlink(input_fifo);
        }
    }
    free(sir);
    free(cuvant);

    return EXIT_SUCCESS;
}
