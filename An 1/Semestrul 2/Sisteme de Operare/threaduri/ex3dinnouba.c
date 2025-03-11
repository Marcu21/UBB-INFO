//Se dau un fișier binar care conține 100.000 de numere aleatoare și un tablou care poate stoca doar 100 de numere.
//Să se determine suma primelor 1000 de numere întregi din acest fișier folosind 10 thread-uri (consumers threads).
//Citirea celor 1000 de numere intregi se va face, pe rând, în variabila buffer folosind alte 10 thread-uri (producers threads).

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>

#define MAX_NUM 100000
#define MAX_THR 10

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int numere[MAX_NUM];
int buffer[100];
int flag = 0;
int sum = 0;

void* produce(void* arg)
{
	int id = *(int*)arg;
	free(arg);
	int st = id * 100;
	int dr = st + 100;
	pthread_mutex_lock(&mtx);
	while(flag == 1)
	{
		printf("[Producer %d] Buffer is full!\n", id);
		pthread_cond_wait(&cond, &mtx);
	}
	printf("[Producer %d] Production started!\n", id);
	int j = -1;
	for(int i = st; i < dr; i++)
	{
		buffer[++j] = numere[i];
	}
	flag = 1;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mtx);
	
	return NULL;
}

void* consume(void* arg)
{
	int id = *(int*)arg;
	free(arg);
	pthread_mutex_lock(&mtx);
	while(flag == 0)
	{
		printf("[Consumer %d] Buffer is empty!\n", id);
		pthread_cond_wait(&cond, &mtx);
	}
	printf("[Consumer %d] Consumption started!\n", id);
	for(int i = 0; i < 100; i++)
	{
		sum += buffer[i];
	}
	flag = 0;
	pthread_cond_broadcast(&cond);
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
	printf("Suma este: %d\n", sum);
	return 0;
}
