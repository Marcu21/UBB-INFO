#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
	//initializez generatorul (valoarea initiala de la care porneste)
	srandom(time(NULL));
	int i = 0;
	while(i<10)
	{
		printf("%d: %d\n", i, 1+rand()%100);
		i++;
	}
	return 0;
}
