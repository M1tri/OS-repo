#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFF_SIZE 1000

int main(int argc, char** argv)
{	
	char file[1000];

	for (int i = 0; i < BUFF_SIZE; i++)
	{
		file[i] = '\0';
	}
	
	printf("Unesite ime datoteke koju ocete da kopirate: ");
	scanf("%s", file);
	
	char* args[BUFF_SIZE];
	
	args[0] = "cp";
	args[1] = file;
	args[2] = "./tmp/kopija2.txt";
	args[3] = NULL;

	if (fork() == 0)
	{
		if (execvp("cp", args) < 0)
		{
			printf("Ne moze kreiramo dete\n");
			exit(-2);
		}
	}
	wait(NULL);

	printf("Uspeh jeeeeeeej!\n");
	return 0;
}
