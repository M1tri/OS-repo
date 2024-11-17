#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

int niz[20] = {};

pthread_mutex_t mut1, mut2;

void* func1(void* args)
{
	while (1)
	{
		pthread_mutex_lock(&mut1);

		int index = rand() % 10;
		int broj = rand() % 100;

		niz[index] = broj;

		pthread_mutex_unlock(&mut1);

		sleep(2);
	}
}

void* func2(void* args)
{
	while (1)
	{
		pthread_mutex_lock(&mut2);

		int index = rand() % 10 + 10;
		int broj = rand() % 100;

		niz[index] = broj;

		pthread_mutex_unlock(&mut2);

		sleep(4);
	}
}


void* func3(void* args)
{
	while (1)
	{
		pthread_mutex_lock(&mut1);
		pthread_mutex_lock(&mut2);

		int index = rand() % 20;
		int broj = rand() % 100;

		niz[index] = broj;

		pthread_mutex_unlock(&mut2);
		pthread_mutex_unlock(&mut1);

		sleep(8);
	}
}

int x = 0;
void* func4(void* args)
{
	while (x < 10)
	{
		pthread_mutex_lock(&mut1);
		pthread_mutex_lock(&mut2);

		for (int i = 0; i < 20; i++)
		{
			printf("%*d",3, niz[i]);
		}
		printf("\n");
		x++;

		pthread_mutex_unlock(&mut2);
		pthread_mutex_unlock(&mut1);

		sleep(5);
	}
}


int main(int argc, char** argv)
{
	pthread_mutex_init(&mut1, NULL);
	pthread_mutex_init(&mut2, NULL);

	pthread_t N1, N2, N3;
	
	pthread_t nit; // nasa
	
	pthread_create(&N1, NULL, func1, NULL);
	pthread_create(&N2, NULL, func2, NULL);
	pthread_create(&N3, NULL, func3, NULL);
	pthread_create(&nit, NULL, func4, NULL);

	pthread_join(nit, NULL);

	pthread_cancel(N1);
	pthread_join(N1, NULL);

	pthread_cancel(N2);
	pthread_join(N2, NULL);

	pthread_cancel(N3);
	pthread_join(N3, NULL);
	
	pthread_mutex_destroy(&mut1);
	pthread_mutex_destroy(&mut2);

	return 0;
}
