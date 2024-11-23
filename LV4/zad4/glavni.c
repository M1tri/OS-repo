#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage ./glavni file.txt\n");
		return -1;
	}

	int pd[2];

	if (pipe(pd) < 0)
	{
		printf("Nesuspesno kreiranje datavoda!\n");
		return -2;
	}

	
	if (fork() == 0)
	{
		close(1);
		dup(pd[1]);

		if (execl(argv[1], argv[1], NULL) < 0)
		{
			printf("Nesupesno kreiranje detete\n");
			return -3;
		}	
	}

	if (fork() == 0)
	{
		close(0);
		dup(pd[0]);
	
		if (execlp("more", "more", NULL) < 0)
		{
			printf("Nesuspenso kreiranje deteta 2\n");
			return -4;
		}
	}

	wait(NULL);
	wait(NULL);
	
	close(pd[0]);
	close(pd[1]);

	return 0;
}
