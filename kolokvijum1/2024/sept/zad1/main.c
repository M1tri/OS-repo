#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

sem_t uneto, odbrojano;
int kraj = 0;

void* func(void* args)
{
	
	int* N = (int*)args;

	while (1)
	{
		sem_wait(&uneto);
		
		if (kraj == 1)
		{
			sem_post(&odbrojano);
			break;
		}

		int i = 0;
		int count = *N;
		while(i <= count)
		{
			printf("%d\n", i);
			i++;
			sleep(2);
		}
		printf("\n");
		sem_post(&odbrojano);
	}

}


int main(int argc, char** argv)
{
	
	sem_init(&uneto, 0, 0);
	sem_init(&odbrojano, 0, 1);

	pthread_t nit;
	int N;
	pthread_create(&nit, NULL, func, (void*)&N);

	while(1)
	{
		sem_wait(&odbrojano);

		printf("Unesite broj: ");
		scanf("%d", &N);
	
		if (N == 999)
		{
			kraj = 1;
			sem_post(&uneto);
			break;		
		}

		sem_post(&uneto);
	}

	pthread_join(nit, NULL);

	sem_destroy(&uneto);
	sem_destroy(&odbrojano);

	return 0;
}
