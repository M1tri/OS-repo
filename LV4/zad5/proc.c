#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		printf("Nepravilno pozvan program!\n");
		return -1;
	}

	int pd[2];

	pd[0] = atoi(argv[1]); // argv[1] == pd[0] 
	pd[1] = atoi(argv[2]); // argv[2] == pd[1]

	close(pd[1]); // jer citamo iz datavoda

	char linija[100];

	for (int i = 0; i < 100; i++)
	{
		linija[i] = '\0';
	}

	while(1)
	{
		int count = read(pd[0], linija, 99);

		if (count == 0)
			break;
	
		for (int i = 0; i < 100; i++)
			printf("%c", linija[i]);
	}

	close(pd[0]);

	return 0;
}
