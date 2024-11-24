#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage ./glavni fajl.txt\n");
		return -1;
	}

	int pd[2];

	if (pipe(pd) < 0)
	{
		printf("Neuspesno kreiranje datavoda!\n");
		return -2;
	}
	
	char str_pd[2][20];
	
	sprintf(str_pd[0], "%d", pd[0]);
	sprintf(str_pd[1], "%d", pd[1]);

	if (fork() == 0)
	{
		if (execl("./dete", "./dete", str_pd[0], str_pd[1], NULL) < 0)
		{
			printf("Greska pri kreairanju deteta!\n");
			return -3;
		}
	}

	close(pd[0]);

	FILE* f;
	f = fopen(argv[1], "r");

	if (f == NULL)
	{
		printf("Fajl ne postoji!\n");
		return -3;
	}

	char linija[100];
	int redBr = 1;
	while(fgets(linija, 100, f) != NULL)
	{
		if (strlen(linija) > 10)
		{
			write(pd[1], &redBr, sizeof(redBr));
			write(pd[1], linija, strlen(linija) + 1);	
		}
		redBr++;
	}
	fclose(f);

	close(pd[1]);
	wait(NULL);

	return 0;
}
