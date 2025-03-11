#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <limits.h>

#define MAX_NUM 70000
#define MAX_THR 10

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;

int numere[MAX_NUM];

int N;

void* doWork(void* arg)
{
	int id = *(int*)arg;
	free(arg);
	int st = id * N / MAX_THR;
	int dr = st + N / MAX_THR;
	int frecventa[10] = {0};
	pthread_mutex_lock(&mtx);
	for(int i = st; i < dr; i++)
	{
//		printf("[Thread %d]: numar %d\n", id, numere[i]);
		frecventa[numere[i]%10]++;
	}
	pthread_mutex_unlock(&mtx);
	pthread_barrier_wait(&barr);
	int media = 0;
	for(int i = 0; i < 10; i++)
		media += frecventa[i];
	media /= 10;
	printf("[Thread %d]: media aritmetica %d\n", id, media);
	int difmin = INT_MAX;
	for(int i = 0; i < 10; i++)
	{
		if(abs(frecventa[i] - media) < difmin)
			difmin = abs(frecventa[i] - media);
	}
	for(int i = 0; i < 10; i++)
	{
		if(abs(frecventa[i] - media) == difmin)
			printf("[Thread %d]: %d\n", id, i);
	}

	return NULL;
}

int main(int argc, char* argv[])
{
	pthread_barrier_init(&barr, NULL, MAX_THR);
	printf("Introdu N: ");
	scanf("%d", &N);
	int fd = open("random-file", O_RDONLY);
	if(fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < N; i++)
		read(fd, &numere[i], 1);
	
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
	pthread_barrier_destroy(&barr);
	return 0;
}
