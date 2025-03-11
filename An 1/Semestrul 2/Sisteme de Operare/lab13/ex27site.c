/*
27. Scrieti un program C care primeste doua numere, N si M, ca argumente la linia de comanda. 
Programul creeaza N thread-uri "generator" care genereaza litere mici ale alfabetului aleator si le adauga unui sir de 
caractere cu 128 de pozitii. Programul mai creeaza un thread "printer" care asteapta ca toate pozitiile sirului de 
caractere sa fie ocupate, moment in care afiseaza sirul si apoi seteaza toate pozitiile sirului la NULL. 
Cele N thread-uri "generator" vor genera M astfel de string-uri iar thread-ul "printer" va afisa fiecare string 
imediat ce ajunge la lungimea 128. Cu variabile globale!
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>

#define SIZE 128

int poz;
int count;
char buffer[SIZE + 1];

pthread_cond_t cg = PTHREAD_COND_INITIALIZER;
pthread_cond_t cp = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;

void* generate(void* arg)
{
	while(1)
	{
		char ch = 'a' + rand() % ('z' - 'a' + 1);

		pthread_mutex_lock(&mtx);
		if(poz == SIZE)
		{
			pthread_cond_signal(&cp);
			while(poz == SIZE)
			{
				pthread_cond_wait(&cg, &mtx);
			}
		}

		if(count == 0)
			break;

		buffer[poz] = ch;
		poz++;
		pthread_mutex_unlock(&mtx);
	}
	pthread_mutex_unlock(&mtx); //din cauza break-ului
	return NULL;
}

void *print(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&mtx);
		if(poz != SIZE)
		{
			pthread_cond_signal(&cg);
			while(poz != SIZE)
			{
				pthread_cond_wait(&cp, &mtx);
			}
		}
		printf("%s\n", buffer);
		memset(buffer, 0, SIZE);
		poz = 0;
		count--;
		pthread_cond_broadcast(&cg);

		if(count == 0)
			break;
		pthread_mutex_unlock(&mtx);
	}
	pthread_mutex_unlock(&mtx);
	return NULL;
}

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("Prea putine argumente!\n");
		exit(1);
	}

	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	poz = 0;
	count = M;

	srand(time(NULL));

	pthread_t tid[N+1];

	for(int i = 0; i < N; i++)
	{
		pthread_create(&tid[i], NULL, generate, NULL);
	}
	pthread_create(&tid[N], NULL, print, NULL);
	for(int i = 0; i <= N; i++)
	{
		pthread_join(tid[i], NULL);
	}

	return 0;
}
