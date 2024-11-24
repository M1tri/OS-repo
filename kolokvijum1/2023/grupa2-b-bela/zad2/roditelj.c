#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv)
{
	int pd1[2]; // roditelj pise detetu
	int pd2[2]; // dete odgovara roditelju

	if (pipe(pd1) < 0)
	{
		printf("Neuspesno kreiranje prvog datavoda");
		return -1;
	}

	if (pipe(pd2) < 0)
	{
		printf("Neuspesno kreiranje drugog datavoda");
		return -2;
	}


	char str_pd1[2][100];
	char str_pd2[2][100];

	sprintf(str_pd1[0], "%d", pd1[0]);
	sprintf(str_pd1[1], "%d", pd1[1]);
	sprintf(str_pd2[0], "%d", pd2[0]);
	sprintf(str_pd2[1], "%d", pd2[1]);

	if (fork() == 0)
	{
		if (execl("./dete", "./dete", str_pd1[0], str_pd1[1], str_pd2[0], str_pd2[1], NULL) < 0)
		{
			printf("Neuspesno kreiranje deteta!\n");
			return -3;
		}
	}


	close(pd1[0]);
	close(pd2[1]);

	char rec[100];
	char odg[100];

	while(1)
	{
		printf("Unesite rec: ");
		fgets(rec, 100, stdin);
		write(pd1[1], rec, strlen(rec) + 1);

		if (strcmp(rec, "END\n") == 0)
		{
			break;
		}

		read(pd2[0], odg, 100);
		if (strcmp(odg, "FOUND") == 0)
		{
			printf("Rec je nadjena u listi!\n");
		}
		else if (strcmp(odg, "NOT FOUND") == 0)
		{
			printf("Rec nije nadjena u listi!\n");
		}
		else
		{
			printf("Ne treba ovo da se desi\n");
		}
	}

	wait(NULL);

	close(pd1[1]);
	close(pd2[0]);

	return 0;
}
