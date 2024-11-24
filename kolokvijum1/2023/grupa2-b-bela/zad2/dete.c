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
		printf("Nepravilno pozvan program!\n");
		return -1;
	}

	int pd1[2];
	int pd2[2];

	pd1[0] = atoi(argv[1]);
	pd1[1] = atoi(argv[2]);
	pd2[0] = atoi(argv[3]);
	pd2[1] = atoi(argv[4]);
	
	char* found = "FOUND";
	char* not_found = "NOT FOUND";
	
	close(pd1[1]);
	close(pd2[0]);

	char rec[100];
	char line[100];
	char* odg;
	int nadjen;
	FILE* f;

	while (1)
	{
		read(pd1[0], rec, 100);
		
		if (strcmp(rec, "END\n") == 0)
			break;

		f = fopen("reci.txt", "r");
		odg = not_found;
		while(fgets(line, 100, f) != NULL)
		{
			if (strcmp(line, rec) == 0)
			{
				odg = found;
				break;		
			}
		}
		fclose(f);
		
		write(pd2[1], odg, strlen(odg) + 1);
	}

	close(pd2[1]);
	close(pd1[0]);

	return 0;
}
