#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

#define SIZE 4

int p1 = 0;
int B1[SIZE] = {};
sem_t sem1;

int p2 = 0;
int B2[SIZE] = {};
sem_t sem2;

int p3 = 0;
int B3[SIZE] = {};
sem_t sem3;

sem_t upis;

void* func0(void *args)
{
	while (1)
	{
		sleep(1);

		sem_wait(&upis);

		sem_wait(&sem3);

		if (p3 < SIZE)
		{
			B3[p3++] = rand() % 100;

			printf("U B3 na poziciji %d je upisano %d\n", p3-1, B3[p3-1]);
			
			sem_post(&sem3);
			
			continue;
		}

		sem_post(&sem3);

		sem_wait(&sem1);

		if (p1 < SIZE)
		{
			B1[p1++] = rand() % 100;

			printf("U B1 na poziciji %d je upisano %d\n", p1-1, B1[p1-1]);

			sem_post(&sem1);

			continue;
		}

		sem_post(&sem1);

		sem_wait(&sem2);

		if (p2 < SIZE)
		{
			B2[p2++] = rand() % 100;

			printf("U B2 na poziciji %d je upisano %d\n", p2-1, B2[p2-1]);

			sem_post(&sem2);

			continue;
		}
		
		sem_post(&sem3);
	}
}


void* func1(void* args)
{
	while (1)
	{
		sem_wait(&sem1);

		if (p1 > 0)
		{
			printf("Iz B1 je sa pozicije %d procitano: %d\n", p1-1, B1[p1-1]);
			p1--;

			sem_post(&upis);
		}

		sem_post(&sem1);

		sleep(rand() % 7);
	}
}

void* func2(void* args)
{
	while (1)
	{
		sem_wait(&sem2);

		if (p2 > 0)
		{
			printf("Iz B2 je sa pozicije %d procitano: %d\n", p2-1, B2[p2-1]);
			p2--;

			sem_post(&upis);
		}

		sem_post(&sem2);

		sleep(rand() % 7);
	}
}


void* func3(void* args)
{
	while (1)
	{
		sem_wait(&sem3);

		if (p3 > 0)
		{
			printf("Iz B3 je sa pozicije %d procitano: %d\n", p3-1, B3[p3-1]);
			
			p3--;
			sem_post(&upis);
		}

		sem_post(&sem3);

		sleep(rand() % 7);
	}
}

int main(int argc, char** argv)
{
	pthread_t N0, N1, N2, N3;

	sem_init(&upis, 0, 3*SIZE);

	sem_init(&sem1, 0, 1);
	sem_init(&sem2, 0, 1);
	sem_init(&sem3, 0, 1);

	pthread_create(&N0, NULL, func0, NULL);
	pthread_create(&N1, NULL, func1, NULL);
	pthread_create(&N2, NULL, func2, NULL);
	pthread_create(&N3, NULL, func3, NULL);
	
	while(1)
	{}

	return 0;

}
