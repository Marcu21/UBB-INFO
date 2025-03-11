#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_SIZE 1024
#define NUM_LETTERS 26

int main(int argc, char* argv[]) {
    FILE *file = fopen("text.txt", "r");
    if (!file) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    char text[MAX_SIZE];
    if (fread(text, sizeof(char), MAX_SIZE, file) <= 0) {
        perror("Failed to read file");
        fclose(file);
        return EXIT_FAILURE;
    }
    fclose(file);

    int i;
    for (i = 0; i < NUM_LETTERS; i++) {
        char input_fifo[20], output_fifo[20];
        char ch = 'a' + i;
        sprintf(input_fifo, "inputfifo%c", ch);
        sprintf(output_fifo, "outputfifo%c", ch);

        mkfifo(input_fifo, 0644);
        mkfifo(output_fifo, 0644);

        pid_t pid = fork();
        if (pid == 0) {  // Child
            int in_fd = open(input_fifo, O_RDONLY);
            int out_fd = open(output_fifo, O_WRONLY);

            char buf[MAX_SIZE];
            read(in_fd, buf, MAX_SIZE);
            close(in_fd);

            // Count frequency
            int count = 0, j;
            for (j = 0; j < strlen(buf); j++) {
                if (buf[j] == ch) count++;
            }

            write(out_fd, &count, sizeof(count));
            close(out_fd);
            exit(0);
        }
    }

    // Parent process
    for (i = 0; i < NUM_LETTERS; i++) {
        char ch = 'a' + i;
        char input_fifo[20], output_fifo[20];
        sprintf(input_fifo, "input_fifo_%c", ch);
        sprintf(output_fifo, "output_fifo_%c", ch);

        int in_fd = open(input_fifo, O_WRONLY);
        int out_fd = open(output_fifo, O_RDONLY);

        write(in_fd, text, strlen(text) + 1);
        close(in_fd);

        int count;
        read(out_fd, &count, sizeof(count));
        printf("%c: %d\n", ch, count);
        close(out_fd);

        unlink(input_fifo);
        unlink(output_fifo);
    }

    return EXIT_SUCCESS;
}
