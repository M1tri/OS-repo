#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <ctype.h>

sem_t upisano, sumirano;
int niz[100];
int brEl;
int s;
int kraj;


void* sumiraj(void* args)
{
	while(1)
	{
		sem_wait(&upisano);
		
		if (kraj)
		{
			sem_post(&sumirano);
			break;
		}

		s = 0;
		for (int i = 0; i < brEl; i++)
		{
			s += niz[i];
		}
					
		sem_post(&sumirano);		
	}
}

int main(int argc, char** argv)
{
	pthread_t nit;

	sem_init(&upisano, 0, 0);
	sem_init(&sumirano, 0, 1);

	pthread_create(&nit, NULL, sumiraj, NULL);

	FILE* f;
	f = fopen("ulaz.txt", "r");

	if (f == NULL)
	{
		printf("Ne postoji fajl!\n");
		return -1;
	}
	
	kraj = 0;
	int flag = 0;
	char linija[100];
	char broj[100];

	while (1)
	{
		sem_wait(&sumirano);

		if (flag == 0)
			flag = 1;
		else
			printf("Suma niza je: %d\n", s);

		fgets(linija, 100, f);
	
		if (feof(f))
		{
			kraj = 1;
			sem_post(&upisano);
			break;
		}
		
		int i = 0;
		int l = strlen(linija);
		brEl = 0;

		while (i < l)
		{
			if (linija[i] == ' ')
			{
				i++;
				continue;
			}
			else if (linija[i] >= '0' && linija[i] <= '9')
			{
				int j = 0;
				while (linija[i] >= '0' && linija[i] <= '9' && i < l)
				{
					broj[j] = linija[i];
					j++;
					i++;
				}
				broj[j] = '\0';
				niz[brEl++] = atoi(broj);

//				printf("%s\n", broj);
			}
			else
			{
				i++;
			}
		}
		
		sem_post(&upisano);
	}

	pthread_join(nit, NULL);

	sem_destroy(&upisano);
	sem_destroy(&sumirano);

	return 0;
}
