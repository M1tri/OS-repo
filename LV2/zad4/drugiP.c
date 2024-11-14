#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define ARGS_MAX 50

int main(int argc, char** argv)
{
	if (argc > ARGS_MAX - 1)
	{
		printf("Previse argumenata\n");
		return -1;	
	}

	char* args[ARGS_MAX];
	
	args[0] = "./prviP";
	for (int i = 1; i < argc; i++)
	{
		args[i] = argv[i];
	}
	args[argc] = NULL;

	if (fork() == 0) // fork() == 0 znaci da samo dete ulazi u ovu granu
	{
		execv("./prviP", args);  
	}
	wait(NULL);

	printf("Ja sam original\n");

	return 0;
}
