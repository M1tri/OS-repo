#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_p, sem_n, mut;

void* func_p(void* args)
{
	char* prva = (char*) args;

	FILE* f;
	f = fopen(prva, "r");

	char linija[100];
	int brLinije = 1;
	while(fgets(linija, 100, f) != NULL)
	{
		sem_wait(&sem_p);
		sem_wait(&mut);

		FILE* zbir = fopen("zbir.txt", "a");
		fprintf(zbir, "%s %d | %s", prva, brLinije, linija);
		fclose(zbir);
		brLinije++;

		sem_post(&mut);
		sem_post(&sem_n);
	}
	fclose(f);
}

void* func_n(void* args)
{
	char* druga = (char*) args;

	FILE* f;
	f = fopen(druga, "r");

	char linija[100];
	int brLinije = 1;
	while(fgets(linija, 100, f) != NULL)
	{
		sem_wait(&sem_n);
		sem_wait(&mut);

		FILE* zbir = fopen("zbir.txt", "a");
		fprintf(zbir, "%s %d | %s", druga, brLinije, linija);
		fclose(zbir);
		brLinije++;

		sem_post(&mut);
		sem_post(&sem_p);
	}
	fclose(f);
}

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("usage ./main file1 file2\n");
		return -1;
	}
	
	pthread_t parna, neparna;

	sem_init(&sem_p, 0, 0);
	sem_init(&sem_n, 0, 1);
	
	sem_init(&mut  , 0, 1);

	pthread_create(&parna, NULL, func_p, (void*)argv[1]);
	pthread_create(&neparna, NULL, func_n, (void*)argv[2]);	
	
	pthread_join(parna, NULL);
	pthread_join(neparna, NULL);

	sem_destroy(&sem_p);
	sem_destroy(&sem_n);
	sem_destroy(&mut);

	return 0;
}
