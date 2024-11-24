#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>


typedef struct 
{
	int* buff;
	int size;

} params;

sem_t upis_p, upis_n, citanje_p, citanje_n;

void* funk_p(void* args)
{
	params* a = (params*)args;

	int* buff = a->buff;
	int size = a->size;
	
	int i = 0;
	while (i < 5)
	{
		sem_wait(&citanje_p);
			
	//	printf("Uso sam u p\n");

		for (int j = 0; j < size; j += 2)
		{
			buff[j] = rand() % 300;
		}

		sem_post(&upis_p);
		i++;
	}
}

void* funk_n(void* args)
{
	params* a = (params*)args;

	int* buff = a->buff;
	int size = a->size;
	
	int i = 0;
	while (i < 5)
	{
		sem_wait(&citanje_n);

	//	printf("Uso sam u n\n");

		for (int j = 1; j < size; j += 2)
		{
			buff[j] = rand() % 300;
		}

		sem_post(&upis_n);
		i++;
	}
}

#define SIZE 10

int main(int argc, char** argv)
{	
	srand((unsigned int)time(NULL));

	pthread_t parna, neparna;
	
	int size = SIZE;
	int buff[SIZE];
	
	sem_init(&upis_p, 0, 0);
	sem_init(&upis_n, 0, 0);

	sem_init(&citanje_p, 0, 1);
	sem_init(&citanje_n, 0, 1);
	
	params P[2];

	P[0].buff = buff;
	P[0].size = size;

	P[1].buff = buff;
	P[1].size = size;

	pthread_create(&parna, NULL, funk_p, (void*)&P[0]);
	pthread_create(&neparna, NULL, funk_n, (void*)&P[1]);

	int i = 0;
	while (i < 5)
	{
		sem_wait(&upis_p);
		sem_wait(&upis_n);
		
		//printf("Uso sam\n");

		int s = 0;
		for (int j = 0; j < size; j++)	
		{
			s += buff[j];
		}
		
		if (s >= 2000)
		{		
			for (int j = 0; j < size; j++)
			{
				printf("%*d ",3, buff[j]); 
			}

			printf("\nSuma: %d\n", s);
		}
		else
		{
			printf("Suma nije veca od 2000, %d\n", s);
		}

		sem_post(&citanje_n);
		sem_post(&citanje_p);
		i++;
	}	
	
	pthread_join(parna, NULL);
	pthread_join(neparna, NULL);

	sem_destroy(&upis_p);
	sem_destroy(&upis_n);
	sem_destroy(&citanje_p);
	sem_destroy(&citanje_n);

	return 0;
}
