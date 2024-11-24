#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("usage ./roditelj ./dete N\n");
		return -1;
	}

	int c_id = fork();

	if (c_id == 0)
	{
		if (execl(argv[1], argv[1], argv[2], NULL) < 0)
		{
			printf("Neuspesno kreiranje deteta\n");
			return -2;
		}
	}

	int c_exit;

	wait(&c_exit);
	
	int status = WEXITSTATUS(c_exit);

	printf("Dete je izaslo sa statusom: %d\n", status);

	return 0;
}
