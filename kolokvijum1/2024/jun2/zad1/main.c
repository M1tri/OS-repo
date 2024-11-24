#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t sem_1, sem_2;
int brojac = 0;

void* func_1(void* args)
{
	int* N = (int*) args;
		
	while(1)
	{
		sem_wait(&sem_1);

		while (brojac <= *N)
		{
			printf("Prva: %d\n", brojac);
			brojac++;
			sem_post(&sem_2);
			break;
		}

		if (brojac > *N)
		{
			sem_post(&sem_2);
			break;
		}
	}
}

void* func_2(void* args)
{
	int* N = (int*) args;

	while(1)
	{
		sem_wait(&sem_2);
		
		while (brojac <= *N)
		{
			if (brojac % 3 != 0)
			{
				printf("Druga: %d\n", brojac);
			}
			else
			{
				sem_post(&sem_1);
				break;
			}
	
			brojac++;
		}

		if (brojac > *N)
		{
			sem_post(&sem_1);
			break;
		}
	}
}

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage ./main N\n");
		return -1;
	}

	int N = atoi(argv[1]);

	sem_init(&sem_1, 0, 1);
	sem_init(&sem_2, 0, 0);

	pthread_t prva, druga;
	
	pthread_create(&prva, NULL, func_1, (void*)&N);
	pthread_create(&druga, NULL, func_2, (void*)&N);

	pthread_join(prva, NULL);
	pthread_join(druga, NULL);

	sem_destroy(&sem_1);
	sem_destroy(&sem_2);

	return 0;
}
