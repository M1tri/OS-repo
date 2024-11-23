#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>

// standarni ulaz je  0
// standarni izlaz je 1

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("usage ./glavni ./program file\n");
		return -1;
	}

	int fd;
	
	fd = open(argv[2], O_CREAT | O_TRUNC | O_RDWR, 0777); // magicna linija

	close(1); // zatvaramo stdout

	dup(fd);	

	if (fork() == 0)
	{
		if (execl("./stampa", "./stampa", NULL) < 0)
		{
			printf("Neuspesno kreiranje deteta\n");
			return -2;
		}
	}

	wait(NULL);

	close(fd);

	return 0;
}
