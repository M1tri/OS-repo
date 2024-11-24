#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
		if (execl("./dete", "./dete", str_pd1[0], str_pd1[1], str_pd2[0], str_pd2[1], NULL) < 0)
		{
			printf("Neuspesno kreiranje prvog dete!\n");
			return -3;
		}
	}
	
	close(pd1[0]);
	close(pd2[1]);

	char recenica[100];
	printf("Unesite recenicu: ");
	fgets(recenica, 100, stdin);

	int l = strlen(recenica);
	
	int i = 0;
	char rec[100];
	int odg;
	while (i < l)
	{
		if (recenica[i] == ' ' || recenica[i] == '\n')
		{
			i++;
		}
		else
		{
			int j = 0;
			while (recenica[i] != ' ' && recenica[i] != '\n' && i < l)
			{
				rec[j] = recenica[i];
				j++;
				i++;
			}	
			rec[j] = '\0';

			write(pd1[1], rec, j);
			read(pd2[0], &odg, sizeof(odg));
			
			printf("Suma cifara u reci %s je %d\n", rec, odg);
		}
	}

	close(pd1[1]);
	close(pd2[0]);
	
	wait(NULL);

	return 0;
}
