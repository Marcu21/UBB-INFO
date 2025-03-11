//2. Se dă un tablou care conține 100.000 de numere întregi. Folosind un număr potrivit de thread-uri
//și cele mai potrivite mecanisme de sincronizare, să se calculeze diferența absolută dintre valoarea minimă
//determinată în fiecare interval de 2000 de numere consecutive și media aritmetică a tuturor valorilor minime.

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>
#include <time.h>
#include <pthread.h>

#define MAX_NUM 100000
#define MAX_THR 50

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

int numere[MAX_NUM];
int dif = 0;
int suma = 0;

void* doMin(void* arg)
{
	int id = *(int*)arg;
	free(arg);
	
	int st = id * MAX_NUM / MAX_THR;
	int dr = st + MAX_NUM / MAX_THR;
	
	int minn = INT_MAX;
	for(int i = st; i < dr; i++)
	{
		if(numere[i] < minn) minn = numere[i];
	}
	printf("[Thread %d] %d\n", id, minn);
	
	pthread_mutex_lock(&mtx);
	dif = abs(dif - minn);
	suma += minn;
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
	
	printf("Diferenta absoluta: %d\n", dif);
	int medie = suma / MAX_THR;
	printf("Media aritmetica: %d\n", medie);
	
	return 0;
}
