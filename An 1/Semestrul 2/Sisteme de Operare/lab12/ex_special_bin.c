//Se dau 100.000 numere aleatoare. Utilizand un numar potrivit de threaduri si cele mai potrivite mecanisme de
//sincronizare sa se determine cea mai mica diferenta dintre 2 numere din oricare (*fiecare) interval de 2000 de numere.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_NUM 100000
#define MAX_THR 50

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
//daca se foloseste pthread_..._init(); trebuie dat pthread_..._destroy(); asta in main inainte sa creez mutexu

int numere[MAX_NUM], minDif = INT_MAX;

void* doDif(void* arg)
{
	int id = *(int*)arg;
	free(arg);
	
	int st = id * MAX_NUM / MAX_THR;
	int dr = st + MAX_NUM / MAX_THR;
	
	int dif = INT_MAX;
	for(int i = st; i < dr - 1; i++)
	{
		for(int j = i + 1; j < dr; j++)
		{
			if (dif > abs(numere[i] - numere[j]))
				dif = abs(numere[i] - numere[j]);
		}
	}
	//avem nevoie de mutex pt ca modificam variabila globala
	pthread_mutex_lock(&mtx);
	if (dif < minDif)
		minDif = dif;
	pthread_mutex_unlock(&mtx);
	
	return NULL;
}

//la examen probabil si mutex si bariera

int main(int argc, char* argv[])
{
	/*
	//generare 100.000 numere aleatoare
	srand(time(NULL));
	for(int i = 0; i < MAX_NUM; i++)
	{
		numere[i] = rand();
	}
	*/
	pthread_t tid[MAX_THR];
	
	//citesc 100000 numere aleatoare
	int fd = open("file.bin", O_RDONLY);
	if ( fd == -1)
	{
		perror("open()");
		exit(1);
	}
	for(int i = 0; i < MAX_NUM; i++)
		read(fd, &numere[i], sizeof(int));
	close(fd);
	
	//fara initializator static
	//pthread_mutex_init(&mtx, NULL);
	
	for(int i = 0; i < MAX_THR; i++)
	{
		int *id = malloc(sizeof(int));
		*id = i;
		pthread_create(&tid[i], NULL, doDif, id);
		//nu se da free aici!
	}
	
	for(int i = 0; i < MAX_THR; i++)
	{
		pthread_join(tid[i], NULL);
	}
	
	//pthread_mutex_destroy(&mtx);
	
	printf("Diferenta minima: %d\n", minDif);
	
	return 0;
}
