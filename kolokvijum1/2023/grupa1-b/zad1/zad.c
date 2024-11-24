#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t sem_g, sem_n;

void* funk(void* args)
{
	int* N = (int*)args;
	
	int count;
	FILE* f;
	char linija[100];

	f = fopen("data.txt", "r");

	while (1)
	{
		sem_wait(&sem_n);	

		count = *N;
		
		if (count == 99)
		{
			sem_post(&sem_g);
			break;
		}

		while(count > 0)
		{
			if (fgets(linija, 100, f) == NULL)
			{
				fclose(f);
				f = fopen("data.txt", "r");
				fgets(linija, 100, f);
			}

			printf("%s", linija);
			count--;
			sleep(1);
		}
	
		sem_post(&sem_g);
	}
}

int main(int argc, char** argv)
{
	pthread_t nit;
	
	sem_init(&sem_g, 0, 1);
	sem_init(&sem_n, 0, 0);

	int N;
	pthread_create(&nit, NULL, funk, (void*)&N); 
	
	while (1)
	{
		sem_wait(&sem_g);

		printf("Unesite broj N: ");
		scanf("%d", &N);

		if (N == 99)
		{
			sem_post(&sem_n);
			break;
		}
	
		sem_post(&sem_n);
	}

	pthread_join(nit, NULL);
	
	sem_destroy(&sem_g);
	sem_destroy(&sem_n);

	return 0;
}
