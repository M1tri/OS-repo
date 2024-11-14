#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage ./zad5 <filename>\n");
		return -1;
	}
	
	if (fork() == 0)
	{
		if (execlp("cp", "cp", argv[1], "./tmp/kopija.txt", NULL) < 0)
		{
			printf("Ne moze kreiramo dete\n");
			exit(-2);
		}
	}
	wait(NULL);

	printf("Uspeh jeeeeeeej!\n");
	return 0;
}
