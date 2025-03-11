#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <pthread.h>
#include <limits.h>

#define MAX_NUM 100000
#define MAX_THR 10
int N;
int numere[MAX_NUM];

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barr;

int prim(int nr)
{
	for(int i = 2; i <= nr/2; i++)
		if(nr % i == 0) return 0;
	return 1;
}

void* doWork(void* arg)
{
	int id = *(int*)arg;
	free(arg);
	int aparitii[100] = {0};
	pthread_mutex_lock(&mtx);
	int st = id * N / MAX_THR;
	int dr = st + N / MAX_THR;
	for(int i = st; i < dr; i++)
	{
		if((numere[i] > 0) && (numere[i] <= 100) & (prim(numere[i])))
			aparitii[numere[i]] += 1;
	}
	pthread_mutex_unlock(&mtx);
	pthread_barrier_wait(&barr);
	int sum = 0, count = 0;
	for(int i = 0; i < 100; i++)
	{
		if(aparitii[i] > 0)
		{
			sum += i * aparitii[i];
			count += aparitii[i];
		}
	}
	float media = sum / count;
	int difmin = INT_MAX;
	printf("[Thread %d]: Media aritmetica: %f \n", id, media);
	for(int i = 0; i < 100; i++)
	{
		if(abs(media - aparitii[i]) < difmin) 
			difmin = abs(media - aparitii[i]);
	}
	for(int i = 0; i < 100; i++)
	{
		if(abs(media - aparitii[i]) == difmin)
			printf("[Thread %d]: numar %d, frecventa %d \n", id, numere[i], aparitii[i]);
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
	pthread_barrier_destroy(&barr);
	return 0;
}
