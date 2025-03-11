#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
#include <pthread.h>
#include <limits.h>

int N;
#define MAX_THR 100
int numere[80000];
int frecventa[101] = {0};

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;

void* doWork(void* arg)
{
	int id = *(int*)arg;
	free(arg);
	int st = id * N / MAX_THR;
	int dr = st + N / MAX_THR;
	float media = 0;
	int count  = 0;
	int difmin = INT_MAX;
	pthread_mutex_lock(&mtx);
	for(int i = st; i < dr; i++)
	{
		if((numere[i] % 2 == 0) && (numere[i] > 0) & (numere[i] <= 100))
			frecventa[numere[i]]++;
	}
	pthread_mutex_unlock(&mtx);
	pthread_barrier_wait(&barr);
	for(int i = 2; i <= 100; i = i + 2)
	{
		media += frecventa[i];
		count++;
	}
	media /= count;
	printf("[Thread %d] Media = %f\n", id, media);
	for(int i = 2; i <= 100; i = i + 2)
	{
		if(difmin > abs(frecventa[i] - media))
			difmin = abs(frecventa[i] - media);
	}
	for(int i = 2; i <= 100; i = i + 2)
	{
		if(difmin == abs(frecventa[i] - media))
			printf("[Thread %d] %d\n", id, i);
	}
	return NULL;
}
	

int main(int argc, char* argv[])
{
	printf("Introdu N:");
	scanf("%d", &N);
	pthread_barrier_init(&barr, NULL, MAX_THR);
	int fd = open("random-file", O_RDONLY);
	if(fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < N; i++)
	{
		read(fd, &numere[i], 1);
	}
	pthread_t tid[MAX_THR];
	for(int i = 0; i < MAX_THR; i++)
	{
		int *id = malloc(sizeof(int));
		*id = i;
		pthread_create(&tid[i], NULL, doWork, id);
	}
	for(int i = 0; i < MAX_THR; i++)
	{
		pthread_join(tid[i], NULL);
	}
	close(fd);
	pthread_barrier_destroy(&barr);
	return 0;
}
