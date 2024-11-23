#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

char* buff;
int buffFull;

int N;
int eof;
int count;

pthread_mutex_t mut;
pthread_cond_t empty, full;

void* citaj(void* args)
{
	char* izlaz = (char*)args;

	FILE* fi;

	fi = fopen(izlaz, "wb");
	
	int done = 0;
	while (1)
	{

		pthread_mutex_lock(&mut);
		while (!buffFull)
		{
			pthread_cond_wait(&full, &mut);
		}

		fwrite(buff, 1, count, fi);

		if (eof == 1)
			done = 1;

		buffFull = 0;
		pthread_cond_signal(&empty);
	
		pthread_mutex_unlock(&mut);
		
		if (done == 1)
			break;
	}
	fclose(fi);
}

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		printf("usage ./zad izvor.txt N izlaz.txt\n");
		return -1;
	}

	N = atoi(argv[2]);
	buff = (char*)malloc(N * sizeof(char));
	buffFull = 0;
	eof = 0;

	FILE* fu;
	fu = fopen(argv[1], "rb");

	if (fu == NULL)
	{
		printf("Ne postoji fajl!\n");
		return -2;
	}
	
	pthread_mutex_init(&mut, NULL);

	pthread_cond_init(&empty, NULL);
	pthread_cond_init(&full, NULL);

	pthread_t nit;
	pthread_create(&nit, NULL, citaj, (void*)argv[3]); 

	while (!feof(fu))
	{
		pthread_mutex_lock(&mut);

		while (buffFull)
		{
			pthread_cond_wait(&empty, &mut);
		}
	
		count =	fread(buff, 1, N, fu);
	
		if (feof(fu))
		{
			eof = 1;
		}

		buffFull = 1;
		pthread_cond_signal(&full);
			
		pthread_mutex_unlock(&mut);	
	}
	fclose(fu);
		
	pthread_join(nit, NULL);

	pthread_mutex_destroy(&mut);
	pthread_cond_destroy(&empty);
	pthread_cond_destroy(&full);
	free(buff);

	return 0;
}
