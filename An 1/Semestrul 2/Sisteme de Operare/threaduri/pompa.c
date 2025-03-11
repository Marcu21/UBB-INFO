#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <limits.h>

#define MAX_THREADS 10
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int fuel = 0;

void* masina(void* arg)
{
	int id = *(int*)arg;
	free(arg);
	pthread_mutex_lock(&mtx);
	while(fuel == 0)
	{
		printf("[Masina %d] nu este combustibil. Astept...\n", id);
		pthread_cond_wait(&cond, &mtx);
	}
	printf("[Masina %d] este combustibil. Alimentez...\n", id);
	fuel = 0;
	printf("[Masina %d] am terminat de alimentat...\n", id);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);
	return NULL;
}

void* pompa(void* arg)
{
	int id = *(int*)arg;
	free(arg);
	pthread_mutex_lock(&mtx);
	while(fuel == 1)
	{
		printf("[Pompa %d] pompa este plina. Astept...\n", id);
		pthread_cond_wait(&cond, &mtx);
	}
	printf("[Pompa %d] pompa este goala. Pompez...\n", id);
	fuel = 1;
	printf("[Pompa %d] pompa este plina...\n", id);
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);
	
	return NULL;
}

int main(int argc, char* argv[])
{
	pthread_t tm[MAX_THREADS];
	pthread_t tp[MAX_THREADS];
	for(int i = 0; i < MAX_THREADS; i++)
	{
		int *idm = malloc(sizeof(int));
		*idm = i;
		int *idp = malloc(sizeof(int));
                *idp = i;
                pthread_create(&tp[i], NULL, pompa, idp);
		pthread_create(&tm[i], NULL, masina, idm);
	}
	for(int i = 0; i < MAX_THREADS; i++)
	{
		pthread_join(tm[i], NULL);
		pthread_join(tp[i], NULL);
	}

	return 0;
}
