#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 6

char recenice[N][20] = {"Ovo", "je", "test", "za", "niti", "!"};
sem_t semafori[N-1];

typedef struct
{
	char* rec;

	sem_t* prev;
	sem_t* curr;
} params;

void* stampaj(void* arg)
{
	params* a = (params*)arg;

	char* rec = a->rec;
	sem_t* prev = a->prev;
	sem_t* curr = a->curr;

	if (prev != NULL)
	{
		sem_wait(prev);
	}

	printf("%s\n", rec);
	sleep(2);

	if (curr != NULL)
	{
		sem_post(curr);
	}
}

int main(int argc, char** argv)
{
	pthread_t niti[N];
	
	for (int i = 0; i < N-1; i++)
	{
		sem_init(&semafori[i], 0, 0); 
	}

	params P[N];
	for (int i = 0; i < N; i++)
	{
		P[i].rec = recenice[i];

		if (i == 0)
		{
			// prva rec
		
			P[i].prev = NULL;	
			P[i].curr = &semafori[i];
		}
		else if (i == N-1)
		{
			// poslednja rec
				
			P[i].prev = &semafori[i-1];
			P[i].curr = NULL;
		}
		else
		{
			P[i].prev = &semafori[i-1];
			P[i].curr = &semafori[i];
		}

		pthread_create(&niti[i], NULL, stampaj, (void*)&P[i]);
	}

	for (int i = 0; i < N; i++)
	{
		pthread_join(niti[i], NULL);
	}

	return 0;
}
