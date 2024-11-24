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
		printf("Ne zoves kako treba!\n");
		return -1;
	}

	int pd[2];

	pd[0] = atoi(argv[1]);
	pd[1] = atoi(argv[2]);

	close(pd[1]);

	char linija[100];
	char buff;
	int redBr;
	int count;

	while(1)
	{
		count = read(pd[0], &redBr, sizeof(redBr));
		
		if (count == 0)
			break;

		int i = 0;
		do
		{
			read(pd[0], &buff, 1);
			linija[i++] = buff;
			
		} while (buff != '\n');

		read(pd[0], &buff, 1);
		linija[i] = buff;
	
		if (redBr % 2 == 0)	
			printf("%d : %s", redBr, linija);
	}
	
	close(pd[0]);

	return 0;
}
