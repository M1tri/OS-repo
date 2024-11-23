#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char** argv)
{
	if (argc != 5)
	{
		printf("Nepravilno pozvan program\n");
		return -1;
	}

	int pd1[2];
	int pd2[2];

	pd1[0] = atoi(argv[1]); // argv[1] == pd1[0]
	pd1[1] = atoi(argv[2]); // argv[2] == pd1[1]

	pd2[0] = atoi(argv[3]); // argv[3] == pd2[0]
	pd2[1] = atoi(argv[4]); // argv[4] == pd2[1]
	
	// Zatvaramo jer ne koristimo
	close(pd1[0]);
	close(pd1[1]);

	close(pd2[1]);

	char recenica[100];
	int kraj = 0;

	do
	{
		read(pd2[0], recenica, 100);

		if (strcmp(recenica, "kraj\n") != 0)
		{	
			int l = strlen(recenica);

			if (l < 99)
			{
				if (recenica[l-2] != '.')
				{
					recenica[l-1] = '.';
					recenica[l] = '\n';
					recenica[l+1] = '\0';
				}
			}

			printf("Drugo dete: %s", recenica);
		}
		else
		{
			kraj = 1;
		}

	} while(!kraj);

	close(pd2[0]);

	return 0;
}
