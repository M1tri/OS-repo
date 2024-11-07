#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_ARGS 20


int main(int argc, char** argv)
{
	char argumenti[MAX_ARGS];
	for (int i = 0; i < argc; i++)
	{
		argumenti[i] = (char*)malloc(strlen(argv[i] + 1) * sizeof(char));
		strcpy(argumenti[i], argv[i]);
	}	

	argumenti[argc] = NULL;
	if (fork() == 0)
	{
		if (execv("./zadatak4a", argumenti) < 0 )
		{
			printf("Doslo je do greske!\n");
		}
	}

	for (int i = 0; < argc; i++)
	{
		free(argv[i]);
	}


	return 0;
}
