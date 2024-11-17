#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

int buffer[2] = {0, 0};
int buffFull;
pthread_mutex_t mut; 
pthread_cond_t full, empty;

void* make(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&mut);
		
		while (buffFull)
		{
			pthread_cond_wait(&empty, &mut);
		}

		buffer[0] = rand() % 11;
		buffer[1] = rand() % 11;
		
		buffFull = 1;
		pthread_cond_signal(&full);

		pthread_mutex_unlock(&mut);

		sleep(rand() % 5);
	}
}


int main(int argc, char** argv)
{
	pthread_mutex_init(&mut, NULL);	
	pthread_cond_init(&full, NULL);
	pthread_cond_init(&empty, NULL);
	buffFull = 0;

	pthread_t nit;
	
	pthread_create(&nit, NULL, make, NULL);

	while (1)
	{
		pthread_mutex_lock(&mut);
		
		while (!buffFull)
		{
			pthread_cond_wait(&full, &mut);
		}

		int n1 = buffer[0];
		int n2 = buffer[1];

		printf("%d + %d = %d\n", n1, n2, n1+n2);
		buffFull = 0;	

		pthread_cond_signal(&empty);

		pthread_mutex_unlock(&mut);
	}

	return 0;
}
