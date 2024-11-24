#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
	int pd1[2];
	int pd2[2];

	if (pipe(pd1) < 0)
	{
		printf("Neuspesno kreiranje prvog datavoda!\n");
		return -1;
	}
	
	if (pipe(pd2) < 0)
	{
		printf("Neuspesno kreiranje drugo datavoda!\n");
		return -2;
	}


	char str_pd1[2][20];
	char str_pd2[2][20];

	sprintf(str_pd1[0], "%d", pd1[0]);	
	sprintf(str_pd1[1], "%d", pd1[1]);
	sprintf(str_pd2[0], "%d", pd2[0]);
	sprintf(str_pd2[1], "%d", pd2[1]);

	if (fork() == 0)
	{
		if (execl("./dete1", "./dete1", str_pd1[0], str_pd1[1], str_pd2[0], str_pd2[1], NULL) < 0)
		{
			printf("Neuspesno kreiranje prvog dete!\n");
			return -3;
		}
	}
	
	if (fork() == 0)
	{
		if (execl("./dete2", "./dete2", str_pd1[0], str_pd1[1], str_pd2[0], str_pd2[1], NULL) < 0)
		{
			printf("Neuspesno kreiranje drugog dete!\n");
			return -4;
		}
	}
		
	close(pd1[0]);
	
	close(pd2[0]);
	close(pd2[1]);

	int N = 10;

	while (N > 0)
	{
		int n = rand() % 100;

		write(pd1[1], &n, sizeof(n));
		N--;
	}
	close(pd1[1]);
	wait(NULL);
	wait(NULL);

	return 0;
}
