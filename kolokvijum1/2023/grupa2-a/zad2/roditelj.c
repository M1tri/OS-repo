#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("usage ./roditelj <file_path> <keyword>\n");
		return -1;
	}

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
			printf("NE moze se napravi dete!\n");
			return -2;	
		}
	}

	close(pd1[0]);
	close(pd2[1]);


	write(pd1[1], argv[1], strlen(argv[1]) + 1);
	write(pd1[1], argv[2], strlen(argv[2]) + 1);
	close(pd1[1]);

	int redBr;
	while (read(pd2[0], &redBr, sizeof(redBr)) > 0)
	{
		printf("Kljucna rec se nalazi u liniji %d\n", redBr);
	}
	close(pd2[0]);

	wait(NULL);

	return 0;
}
