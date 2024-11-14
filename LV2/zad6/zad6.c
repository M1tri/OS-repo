#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>

#define N 3

int mat[N][N];

void* sort(void* arg)
{
	int* vrsta = (int*)arg;
	
	for (int i = 0; i < N-1; i++)
	{
		for (int j = i+1; j < N; j++)
		{
			if (vrsta[i] < vrsta[j])
			{
				int tmp = vrsta[i];
				vrsta[i] = vrsta[j];
				vrsta[j] = tmp;
			}
		}
	}
	printf("Sortirao sam vrstu sa prvim elementom: %d\n", vrsta[0]);	
}	

void printMatrix(int A[N][N], int dim)
{
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			printf("%d ", A[i][j]);
		}
		printf("\n");
	}
}





int main(int argc, char** argv)
{ 
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("A[%d][%d] = ", i, j);
			scanf("%d", &mat[i][j]);
		}
	
	}	

	printf("Uneta matrica nesortirana:\n");
	printMatrix(mat, N);	
	
	pthread_t niti[N];

	for (int i = 0; i < N; i++)
	{
		pthread_create(&niti[i], NULL, sort, (void*)mat[i]);
	}
	
	for (int i = 0; i < N; i++)
	{
		pthread_join(niti[i], NULL);
	}

	printf("Sortirano (nadam se):\n");
	printMatrix(mat, N);

	return 0;
}
