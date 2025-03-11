//Se dau un fișier binar care conține 100.000 de numere aleatoare și un tablou care poate stoca doar 100 de numere.
//Să se determine suma primelor 1000 de numere întregi din acest fișier folosind 10 thread-uri (consumers threads).
//Citirea celor 1000 de numere intregi se va face, pe rând, în variabila buffer folosind alte 10 thread-uri (producers threads).

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_THR 10
#define MAX_SIZE 100

int buffer[100];
int fd;
int sum = 0;

int flag = 0; //0 inseamna ca bufferul e gol, 1 inseamna ca bufferul e plin
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* produce(void* arg)
{
	int id = *(int*)arg;
	free(arg);
	//blocam mutex ca accesam variabila
	pthread_mutex_lock(&mtx);
	while(flag == 1)
	{
		printf("[Producer %2d] astept...\n", id);
		pthread_cond_wait(&cond, &mtx);
		//INTREBARE DE EXAMEN!!!
		//de ce primeste ca argument mutexul? pt ca il deblocheaza temporar, altfel alte threaduri nu ar mai putea testa conditia
	}
	printf("[Producer %2d] am inceput producerea...\n", id);
	for(int i = 0; i < MAX_SIZE; i++)
	{
		read(fd, &buffer[i], 2);
		//2 in loc de sizeof(int) sa nu fie numere prea mari pt suma
	}
	flag = 1;
	pthread_cond_signal(&cond);
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
		printf("[Consumer %2d] astept...\n", id);
		pthread_cond_wait(&cond, &mtx);
	}
	printf("[Consumer %2d] am inceput consumarea...\n", id);
	for(int i = 0; i < MAX_SIZE; i++)
	{
		sum += buffer[i];
	}
	flag = 0;
	pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mtx);

	return NULL;
}


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

	//citesc 100000 numere aleatoare
	int fd = open("file.bin", O_RDONLY);
	if ( fd == -1)
	{
		perror("open()");
		exit(1);
	}


	pthread_t tc[MAX_THR];
	pthread_t tp[MAX_THR];

	for(int i = 0; i < MAX_THR; i++)
	{
		int *idc = malloc(sizeof(int));
		*idc = i;
		int *idp = malloc(sizeof(int));
		*idp = i;
		pthread_create(&tc[i], NULL, consume, idc);
		pthread_create(&tp[i], NULL, produce, idp);
		//nu se da free aici!
		//atentie sa nu se dea dublu free (mai bine nu dai free gionule)
	}

	for(int i = 0; i < MAX_THR; i++)
	{
		pthread_join(tc[i], NULL);
		pthread_join(tp[i], NULL);
	}
	printf("Suma: %d\n", sum);
	close(fd);
	return 0;
}
