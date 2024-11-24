#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc != 5)
	{
		printf("Nepravilno pozvan program!\n");
		return -1;
	}

	int pd1[2];
	int pd2[2];

	pd1[0] = atoi(argv[1]);
	pd1[1] = atoi(argv[2]);
	pd2[0] = atoi(argv[3]);
	pd2[1] = atoi(argv[4]);

	
	close(pd1[1]);

	close(pd2[0]);

	char datoteka[100];
	char keyword[100];

	char buff;
	
	int i = 0;

	do
	{
		read(pd1[0], &buff, 1);
		datoteka[i++] = buff;

	} while(buff != '\0');

	i = 0;

	do
	{
		read(pd1[0], &buff, 1);
		keyword[i++] = buff;

	} while(buff != '\0');

	close(pd1[0]);
	
	FILE* f;
	f = fopen(datoteka, "r");

	if (f == NULL)
	{
		printf("Ne postoji fajl!\n");
		return -2;
	}

	char linija[100];
	int redBr = 1;
	while (fgets(linija, 100, f) != NULL)
	{
		if (strstr(linija, keyword) != NULL)
		{
			write(pd2[1], &redBr, sizeof(redBr));
		}	
		redBr++;
	}
	fclose(f);

	close(pd2[1]);

	return 0;
}	
