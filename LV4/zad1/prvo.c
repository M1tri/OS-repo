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
	
	close(pd1[1]); // Iz pd1 cita

	close(pd2[0]); // Iz pd2 pise
	
	char recenica[100];
	int kraj = 0;

	do
	{
		read(pd1[0], recenica, 100);
		
		if (strcmp(recenica, "kraj\n") != 0)
		{	
			if (recenica[0] > 'a' && recenica[0] < 'z')
			{
				recenica[0] -= 32;
			}

			printf("Prvo dete: %s", recenica);
		}
		else
		{
			kraj = 1;
		}

		write(pd2[1], recenica, strlen(recenica) + 1);

	} while (!kraj);

	// mremo pa nam ne treba
	close(pd1[0]);
	close(pd2[1]); 

	return 0;
}