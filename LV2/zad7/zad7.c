#include <stdio.h>
#include <pthread.h>

#define N 4

char recenica[N][20] = {"Dime", "i", "Dunja", "<3"};

typedef struct
{
	char* str;
	pthread_t* prev;
} params;

void* stampaj(void* args)
{
	params* argumenti = (params*)args;
	
	char* str = argumenti->str;
	pthread_t* prev = argumenti->prev;
	
	if (prev != NULL)
	{
		pthread_join(*prev, NULL);
	}

	printf("%s\n", str);
}

int main(int argc, char** argv)
{
	pthread_t niti[N];
	
	params p1;
	p1.str = recenica[0];
	p1.prev = NULL;
	pthread_create(&niti[0], NULL, stampaj, (void*)&p1);	
	
	params P[N-1];
	for (int i = 1; i < N; i++)
	{
		P[i-1].str = recenica[i];
		P[i-1].prev = &niti[i-1];

		pthread_create(&niti[i], NULL, stampaj, (void*) &P[i-1]);
	}

	/*
	for (int i = 0; i < N; i++)
	{
		pthread_join(niti[i], NULL);
	}
	*/

	pthread_join(niti[N-1], NULL);
	
	return 0;
}
