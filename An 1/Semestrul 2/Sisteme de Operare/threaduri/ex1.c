//1. Se dă un tablou care conține 100.000 de numere întregi. Folosind un număr potrivit de thread-uri
//și cele mai potrivite mecanisme de sincronizare, să se determine cel mai mic număr întreg din acest tablou.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_NUM 100000
#define MAX_THR 100

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int numere[MAX_NUM];
int nrMin = INT_MAX;

void* doMin(void* arg)
{
	int id = *(int*)arg;
	free(arg);
	
	int st = id * MAX_NUM / MAX_THR;
	int dr = st + MAX_NUM / MAX_THR;
	
	int minn = INT_MAX;
	for(int i = st; i < dr; i++)
	{
		if (numere[i] < minn) minn = numere[i];
		printf("[Thread %d] %d\n", id, numere[i]);
	}
	
	pthread_mutex_lock(&mtx);
	if (minn < nrMin) nrMin = minn;
	pthread_mutex_unlock(&mtx);
	
	return NULL;
}

int main(int argc, char* argv[])
{
	srand(time(NULL));
	for(int i = 0; i < MAX_NUM; i++)
	{
		numere[i] = rand();
	}
	
	pthread_t tid[MAX_THR];
	for(int i = 0; i < MAX_THR; i++)
	{
		 int *id = malloc(sizeof(int));
		 *id = i;
		 pthread_create(&tid[i], NULL, doMin, id);
	}
	
	for(int i = 0; i < MAX_THR; i++)
	{
		pthread_join(tid[i], NULL);
	}
	
	printf("Numarul minim este: %d\n", nrMin);
	
	return 0;
}
	
