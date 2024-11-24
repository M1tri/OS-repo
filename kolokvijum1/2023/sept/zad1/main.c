#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int buff[10];
int kraj = 0;

sem_t upisano, procitano;

void* func(void* args)
{
	
	while (1)
	{
		sem_wait(&procitano);

		if (kraj == 1)
		{
			sem_post(&upisano);
			break;
		}

		for (int i = 0; i < 10; i++)
		{
			buff[i] = rand() % 200;
		}
	
		sem_post(&upisano);

		sleep(rand() % 5 + 1);
	}
}

int main(int argc, char** argv)
{
	pthread_t nit;

	sem_init(&upisano, 0, 0);
	sem_init(&procitano, 0, 1);

	pthread_create(&nit, NULL, func, NULL);

	while (1)
	{
		sem_wait(&upisano);

		int s = 0;

		for (int i = 0; i < 10; i++)
		{
			s += buff[i];
		}	
		
		if (s > 1250)
		{
			kraj = 1;
			sem_post(&procitano);
			break;
		}

		printf("Suma: %d\n", s);

		sem_post(&procitano);
	}

	pthread_join(nit, NULL);

	sem_destroy(&upisano);
	sem_destroy(&procitano);

	return 0;
}
