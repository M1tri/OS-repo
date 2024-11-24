#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>


int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("usage ./roditelj input.txt output.txt\n");
		return -1;
	}

	int pd[2];

	if (pipe(pd) < 0)
	{
		printf("Neuspesno kreiranje datavoda\n");
		return -2;
	}
	
	char str_pd[2][20];

	sprintf(str_pd[0], "%d", pd[0]);
	sprintf(str_pd[1], "%d", pd[1]);
	
	if (fork() == 0)
	{
		if (execl("./dete", "./dete", str_pd[0], str_pd[1], argv[2], NULL) < 0)
		{
			printf("Neuspesno kreiranje deteta\n");
			return -3;
		}
	}
	
	close(pd[0]);

	FILE* f = fopen(argv[1], "rb");

	unsigned char buffer[300];
	int count;

	while (!feof(f))
	{
		count = fread(buffer, 1, 200, f);
		write(pd[1], buffer, count);
	}

	close(pd[1]);
	wait(NULL); // nek umre dete necu porok


	return 0;
}
