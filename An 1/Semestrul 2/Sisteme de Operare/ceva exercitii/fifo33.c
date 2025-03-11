#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#define MAX_SIZE 100

int main(int argc, char* argv[])
{
        FILE* fd = fopen("text.txt", "r");
        if (fd==NULL)
        {
                perror("fd()");
                exit(EXIT_FAILURE);
        }
	char* fifo = "./fifo_____33";
        int res = mkfifo(fifo, 0644);
        if(res==-1)
        {
                 perror("mkfifo()");
                 exit(EXIT_FAILURE);
        }
        char *sir = malloc(sizeof(char)*MAX_SIZE);
        char* cuvant = malloc(sizeof(char)*MAX_SIZE);
        fscanf(fd, "%s", cuvant);
        strcpy(sir, cuvant);
        while(fscanf(fd,"%s",cuvant)>0) strcat(sir, cuvant);
        for(char ch='a';ch<='z';ch++)
        {
                int pid = fork();
                if(pid==-1)
                {
                        perror("fork()");
                        exit(EXIT_FAILURE);
                }
                else if(pid==0)
                {
			int pd = open(fifo, O_WRONLY);
                        int frec = 0;
                        for(int i = 0;i<strlen(sir);i++)
                                if(sir[i]==ch) frec++;
                        write(pd, &ch, sizeof(char));
                        write(pd, &frec, sizeof(int));
                        close(pd);
			exit(EXIT_SUCCESS);
                }
                else
                {
                        wait(NULL);
                        //int pd = open(fifo, O_RDONLY);
                        //int frec;
                        //char ch;
                        //read(pd, &ch, sizeof(char));
                        //read(pd, &frec, sizeof(int));
                        //printf("Frecventa aparitiei caracterului %c este %d\n", ch, frec);
                        //close(pd);
	//		unlink(fifo);
//                      exit(EXIT_SUCCESS);
                }
        }
	unlink(fifo);
        free(sir);
        free(cuvant);
}
