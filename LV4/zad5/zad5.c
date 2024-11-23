#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage ./zad5 fajl.txt\n");
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
		if (execl("./proc", "./proc", str_pd[0], str_pd[1], NULL) < 0)
		{
			printf("Neuspesno kreiranje deteta!\n");
			return -3;
		}
	
	}
		
	close(pd[0]); // jer pisem

	FILE* f;
	f = fopen(argv[1], "r");

	if (f == NULL)
	{
		printf("Neuspesno otvaranje fajla!\n");
		return -4;
	}

	
	char linija[100];
	while (fgets(linija, 100, f) != NULL)
	{
	//	printf("Roditelj: %s", linija);
		write(pd[1], linija, strlen(linija) + 1);
	}
	fclose(f);
	
	close(pd[1]);

	printf("cekam dete\n");
	wait(NULL); // cekamo da dete umre

	return 0;
}
