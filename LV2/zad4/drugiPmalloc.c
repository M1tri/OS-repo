#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define ARGS_MAX 50

int main(int argc, char** argv)
{
	if (argc > ARGS_MAX - 1)
	{
		printf("Previse argumenata\n");
		return -1;	
	}

	char** args = (char**)malloc((argc * sizeof(char*)) + 1);
	
	if (args == NULL)
	{
		printf("RAM je pun jebiga\n");
		return -2;
	}

	args[0] = "./prviP";
	for (int i = 1; i < argc; i++)
	{
		args[i] = argv[i];
	}
	args[argc] = NULL;

	if (fork() == 0)
	{
		if (execv("./prviP", args) < 0)
		{
			printf("Nismo uspeli da napravimo dete\n");
			exit(-3);
		}	
	}
	wait(NULL); // cekamo da dete umre

	printf("Umrelo mi dete\n");
	free(args);

	return 0;
}
