#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


int A = 0;
int N = 0;

sem_t sem_N, sem_BP;

void write_BP()
{
	A = A + rand() % 10;
	printf("A je promenjeno na %d\n", A);
	sleep(rand() % 3);
}

void read_BP(int n)
{
	printf("Procitao sam A = %d a ja sam citalac broj %d\n", A, n);
	sleep(rand() % 2);
}

void* pisi(void* args)
{
	while (1)
	{
		sem_wait(&sem_BP);
	
		write_BP();

		sem_post(&sem_BP);
		sleep(rand() % 4);
	}
}


void* citaj(void* args)
{
	while (1)
	{
		sem_wait(&sem_N);
	
		N++;

		if (N == 1)
			sem_wait(&sem_BP);

		sem_post(&sem_N);

		read_BP(N);

		sem_post(&sem_N);

		N--;

		if (N == 0)
			sem_post(&sem_BP);

		sem_post(&sem_N);

		sleep(rand() % 20);
	}
}

int main(int argc, char** argv)
{
	pthread_t pisac;
	pthread_t citaoci[4];	

	sem_init(&sem_N, 0, 1);
	sem_init(&sem_BP, 0, 1);

	pthread_create(&pisac, NULL, pisi, NULL);
	for (int i = 0; i < 4; i++)
	{
		pthread_create(&citaoci[i], NULL, citaj, NULL);
	}
	
	while(1) {}

	return 0;
}
