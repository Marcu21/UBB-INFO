#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/wait.h>
#include <time.h>
#include <limits.h>

#define MAX_NUM 1000
#define MAX_THR 10

int fd;
int buffer[100];
int sum = 0;
int flag = 0;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* consumer(void* arg)
{
        int id = *(int*)arg;
        //free(arg);

        printf("[Consumer %d] Starting ...\n", id);
        pthread_mutex_lock(&mtx);
        while(flag==0)
        {
                printf("[Consumer %d] Buffer is empty. I'm waiting to become full ...\n", id);
                pthread_cond_wait(&cond, &mtx);
        }
        printf("[Consumer %d] Buffer is full. Start consumption ...\n", id);

        int st = id * MAX_NUM / MAX_THR;
        int dr = st + MAX_NUM / MAX_THR;
        for(int i = 0; i < 100; i++)
        {
                sum += buffer[i];
        }

        flag = 0;
        printf("[Consumer %d] Finished consumption. Buffer is now empty.\n", id);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);

        return NULL;
}

void* producer(void* arg)
{
        int id = *(int*)arg;
        //free(arg);
        printf("[Producer %d] Starting ...\n", id);

        pthread_mutex_lock(&mtx);
        while(flag==1)
        {
                printf("[Producer %d] Buffer is full. I'm waiting to become empty ...\n", id);
                pthread_cond_wait(&cond, &mtx);
        }
        printf("[Producer %d] Buffer is empty. Start production ...\n", id);

        int st = id * MAX_NUM / MAX_THR;
        int dr = st + MAX_NUM / MAX_THR;
        for(int i = 0; i < 100; i++)
	{
                read(fd, &buffer[i], sizeof(int));
        }
        flag = 1;
        printf("[Producer %d] Finished production. Buffer is now full.\n", id);

        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mtx);

        return NULL;
}


int main(int argc, char* argv[])
{
        fd = open("random-file", O_RDONLY);
        if (fd == -1)
        {
                perror("open()");
                exit(EXIT_FAILURE);
        }

        pthread_t tc[MAX_THR];
        pthread_t tp[MAX_THR];
        for(int i = 0; i < MAX_THR; i++)
        {
                int *id = malloc(sizeof(int));
                *id = i;
                pthread_create(&tp[i], NULL, producer, id);
                pthread_create(&tc[i], NULL, consumer, id);
        }
        for(int i = 0; i < MAX_THR; i++)
        {
                pthread_join(tp[i], NULL);
                pthread_join(tc[i], NULL);
        }

        printf("Suma: %d\n", sum);
        close(fd);
        return 0;
}
