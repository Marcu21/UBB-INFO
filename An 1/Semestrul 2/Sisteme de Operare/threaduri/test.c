#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <limits.h>

#define MAX_THR 10
#define MAX_NUM 1000

int buffer[100];
int flag = 0;
int sum = 0;
int fd;

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* produce(void* arg)
{
        int id = *(int*)arg;
        //free(arg);
        printf("[Producer %d] starting...\n", id);
        pthread_mutex_lock(&mtx);
        while(flag == 1)
        {
                printf("[Producer %d] buffer is full. I'm waiting...\n", id);
                pthread_cond_wait(&cond, &mtx);
        }
        printf("[Producer %d] producing...\n", id);
        for(int i = 0; i < 100; i++)
        {
                printf("Hatz gion\n");
                read(fd, &buffer[i], sizeof(int));
        }
        flag = 1;
        printf("[Producer %d] finished production...\n", id);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);

        return NULL;
}

void* consume(void* arg)
{
	int id = *(int*)arg;
        //free(arg);
        printf("[Consumer %d] starting...\n", id);
        pthread_mutex_lock(&mtx);
        while(flag == 0)
        {
                printf("[Consumer %d] buffer is empty. I'm waiting...\n", id);
                pthread_cond_wait(&cond, &mtx);
        }
        printf("[Consumer %d] consuming...\n", id);
        for(int i = 0; i < 100; i++)
        {
                sum += buffer[i];
        }
        flag = 0;
        printf("[Consumer %d] finished consumption...\n", id);
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);

        return NULL;
}

int main(int argc, char* argv[])
{
        int fd = open("random-file", O_RDONLY);
        if(fd == -1)
        {
                perror("open()");
                exit(EXIT_FAILURE);
        }
        pthread_t tp[MAX_THR];
        pthread_t tc[MAX_THR];
        for(int i = 0; i < MAX_THR; i++)
        {
                int *idp = malloc(sizeof(int));
                *idp = i;
                int *idc = malloc(sizeof(int));
                *idc = i;
                pthread_create(&tp[i], NULL, produce, idp);
                pthread_create(&tc[i], NULL, consume, idc);
        }
        for(int i = 0; i < MAX_THR; i++)
        {
                pthread_join(tp[i], NULL);
                pthread_join(tc[i], NULL);
        }
        printf("Suma este %d\n", sum);
	close(fd);
	return 0;
}
