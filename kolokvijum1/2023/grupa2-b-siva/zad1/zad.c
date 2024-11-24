#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

char linija[100];
int kraj;

sem_t sem_p, sem_n;
sem_t mut;
sem_t upis, citanje;

void* func_p(void* args)
{
	FILE* f;
	f = fopen("parni.txt", "a");

	while(1)
	{
		sem_wait(&sem_p);
	//	printf("imam p\n");		
		sem_wait(&upis);
	//	printf("imam upis\n");
		sem_wait(&mut);
	//	printf("imam mut\n");

		if (kraj)
		{
			sem_post(&mut);
			sem_post(&upis);
			sem_post(&sem_n);
	//		printf("doslo p\n");
			break;
		}

		fprintf(f, "%s", linija);
	//	printf("%s", linija);
		sem_post(&mut);

		sem_post(&citanje);

		sem_post(&sem_n);
		
	}
//	printf("tuj sam\n");
	fclose(f);
}

void* func_n(void* args)
{
	
	FILE* f;
	f = fopen("neparni.txt", "a");

	while(1)
	{
		sem_wait(&sem_n);

		sem_wait(&upis);

		sem_wait(&mut);
		
		if (kraj)
		{
			sem_post(&mut);
			sem_post(&upis);
			sem_post(&sem_p);

//			printf("doslo n\n");
			break;
		}

		fprintf(f, "%s", linija);
//		printf("%s", linija);

		sem_post(&mut);

		sem_post(&citanje);

		sem_post(&sem_p);	
	}

	fclose(f);
}


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage ./zad fajl.txt\n");
		return -1;
	}
	
	kraj = 0;

	sem_init(&mut, 0, 1);

	sem_init(&sem_p, 0, 0);
	sem_init(&sem_n, 0, 1);

	sem_init(&upis, 0, 0);
	sem_init(&citanje, 0, 1);

	pthread_t parna, neparna;	
	
	pthread_create(&parna, NULL, func_p, NULL);
	pthread_create(&neparna, NULL, func_n, NULL);

	FILE* f;
	f = fopen(argv[1], "r");

	if (f == NULL)
	{
		printf("Greska pri otvaranju fajla!\n");
		return -1;
	}
	
	while (1)
	{
		sem_wait(&citanje);

		sem_wait(&mut);

		if (fgets(linija, 100, f) == NULL)
		{
			kraj = 1;
			sem_post(&mut);
			sem_post(&upis);

//			printf("kraj\n");
			break;
		}

		sem_post(&mut);
		
		sem_post(&upis);
	}

	pthread_join(parna, NULL);
	pthread_join(neparna, NULL);

	sem_destroy(&mut);
	sem_destroy(&sem_p);
	sem_destroy(&sem_n);
	sem_destroy(&upis);
	sem_destroy(&citanje);

	return 0;
}
