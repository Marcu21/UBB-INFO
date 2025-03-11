/*
31. Scrieti un program C care primeste un numar N ca argument la linia de comanda.
Programul creeaza N thread-uri care vor genera numere aleatoare intre 0 si 111111 (inclusiv) pana cand un thread
va genera un numar divizibil cu 1001. Thread-urile vor afisa numerele generate, iar ultimul numar afisat trebuie sa fie
cel divizibil cu 1001. Niciun thread nu va incepe sa genereze numere pana cand toate celelalte thread-uri au fost 
create.Nu se vor folosi variabile globale. (Ba folosim)
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int stop = 0;
pthread_barrier_t bar;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* do_work(void* arg)
{
	pthread_barrier_wait(&bar);
	while(1)
	{
		pthread_mutex_lock(&mtx);
		if(stop == 0)
		{
			int n = rand() % 111112;
			printf("%d\n", n);
			if(n % 1001 == 0)
			{
				stop = 1;
				break;
			}
		}
		else break;
		pthread_mutex_unlock(&mtx);
	}
	pthread_mutex_unlock(&mtx);

	return NULL;
}

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("Prea putine argumente!\n");
		exit(EXIT_FAILURE);
	}

	int n = atoi(argv[1]);
	srand(time(NULL));
	pthread_barrier_init(&bar, NULL, n);

	pthread_t tid[n];
	for(int i = 0; i < n; i++)
	{
		pthread_create(&tid[i], NULL, do_work, NULL);
	}
	for(int i = 0; i < n; i++)
	{
		pthread_join(tid[i], NULL);
	}
	pthread_barrier_destroy(&bar);

	return 0;
}
