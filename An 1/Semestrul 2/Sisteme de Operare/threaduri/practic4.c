#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>

int N, K, MAX_THR, nr = 0;
int numere[80000];
pthread_mutex_t mtx;

void* citire(void* arg)
{
	int n = *(int*)arg;
	free(arg);
	int fd = open("random-file", O_RDONLY);
	if(fd == -1)
	{
		perror("open()");
		exit(EXIT_FAILURE);
	}
	for(int i = 0; i < n; i++)
		read(fd, &numere[i], 1);
	close(fd);
	return NULL;
}

void* doWork(void* arg)
{
	int id = *(int*)arg;
	free(arg);
	int st = id * N / MAX_THR;
	int dr = st + N / MAX_THR;
	pthread_mutex_lock(&mtx);
	int div = 0;
	for(int i = st; i < dr; i++)
	{
		if(numere[i] % K == 0) div++;
	}
	nr += div;
	pthread_mutex_unlock(&mtx);
	printf("[Thread %d] %d\n", id, div);
	return NULL;
}

int main(int argc, char* argv[])
{
	printf("Introdu N:");
	scanf("%d", &N);
	printf("Introdu K:");
	scanf("%d", &K);
	
	int *n = malloc(sizeof(int));
	*n = N;
	pthread_t tc[1];
	pthread_create(&tc[0], NULL, citire, n);
	pthread_join(tc[0], NULL);
	
	MAX_THR = N / 2000;
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
	
	printf("Numere divizibile: %d\n", nr);
	
	return 0;
}
