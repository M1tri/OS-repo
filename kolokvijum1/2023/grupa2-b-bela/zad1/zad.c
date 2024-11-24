#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>
#include <ctype.h>

char recenica[100];

sem_t glavna, prva, druga;
pthread_mutex_t mut;

void* func1(void* args)
{
	int kraj = 0;

	do
	{
		sem_wait(&prva);
		pthread_mutex_lock(&mut);

		if (strcmp(recenica, "KRAJ\n") == 0)
			kraj = 1;

		if (!kraj)
		{
			if (recenica[0] >= 'a' && recenica[0] <= 'z')
			{
				recenica[0] = toupper(recenica[0]);
			}

			int l = strlen(recenica);

			if (l < 99)
			{
				if(recenica[l-2] != '.')
				{
					recenica[l-1] = '.';
					recenica[l] = '\n';
					recenica[l+1] = '\0';
				}
			}

			printf("Prva: %s", recenica);
		}

		pthread_mutex_unlock(&mut);
		sem_post(&druga);

	} while(!kraj);
}

void* func2(void* args)
{
	int kraj = 0;

	do
	{
		sem_wait(&druga);
		pthread_mutex_lock(&mut);

		if (strcmp(recenica, "KRAJ\n") == 0)
			kraj = 1;

		if (!kraj)
		{
			int l = strlen(recenica);

			for (int i = 0; i < l; i++)
			{
				if (recenica[i] == ' ')
				{
					recenica[i] = '_';
				}
			}

			printf("Treca: %s", recenica);
		}

		pthread_mutex_unlock(&mut);
		sem_post(&glavna);

	} while(!kraj);
}


int main(int argc, char** argv)
{
	pthread_t prva_nit, druga_nit;

	sem_init(&glavna, 0, 1);
	sem_init(&prva, 0, 0);
	sem_init(&druga, 0, 0);
	
	pthread_mutex_init(&mut, NULL);

	pthread_create(&prva_nit, NULL, func1, NULL);
	pthread_create(&druga_nit, NULL, func2, NULL);

	int kraj = 0;
	do
	{
		sem_wait(&glavna);
		pthread_mutex_lock(&mut);

		fgets(recenica, 100, stdin);

		if (strcmp(recenica, "KRAJ\n") == 0)
			kraj = 1;

		pthread_mutex_unlock(&mut);
		sem_post(&prva);

	} while(!kraj);

	pthread_join(prva_nit, NULL);
	pthread_join(druga_nit, NULL);

	pthread_mutex_destroy(&mut);
	sem_destroy(&glavna);
	sem_destroy(&prva);
	sem_destroy(&druga);

	return 0;
}
