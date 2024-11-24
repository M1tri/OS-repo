#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

sem_t uneto, odbrojano;
int kraj = 0;

void* func(void* args)
{
	int* N = (int*)args;

	while(1)
	{
		
		sem_wait(&uneto);
		
		if (kraj)
		{
			sem_post(&odbrojano);
			break;
		}

		int count = *N;

		while(count >= 0)
		{
			printf("%d\n", count);
			count--;
			sleep(1);
		
		}

		sem_post(&odbrojano);
	}
}

int main(int argc, char** argv)
{
	char buff[100];
	pthread_t nit;
	
	sem_init(&uneto, 0, 1);
	sem_init(&odbrojano, 0, 0);

	printf("Unesite broj (ili KRAJ): ");
	scanf("%s", buff);
	
	if (strcmp(buff, "KRAJ") == 0)
		return 0;
	
	int N = atoi(buff);

	pthread_create(&nit, NULL, func, (void*)&N);
	

	while(1)
	{
		sem_wait(&odbrojano);
		
		printf("Unesite broj (ili KRAJ): ");
		scanf("%s", buff);

		if (strcmp(buff, "KRAJ") == 0)
		{
			kraj = 1;
			sem_post(&uneto);
			break;
		}	

		N = atoi(buff);

		sem_post(&uneto);
	}

	pthread_join(nit, NULL);

	sem_destroy(&uneto);
	sem_destroy(&odbrojano);

	return 0;
}
