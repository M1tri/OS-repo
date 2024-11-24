#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/file.h>

int main(int argc, char** argv)
{
	if (argc != 5)
	{
		printf("Nepravilno pozvan program\n");
		return -1;
	}

	int pd1[2];
	int pd2[2];

	pd1[0] = atoi(argv[1]);
	pd1[1] = atoi(argv[2]);
	pd2[0] = atoi(argv[3]);
	pd2[1] = atoi(argv[4]);

	close(pd1[0]);
	close(pd1[1]);

	close(pd2[1]);

	int f = open("redirekcija.txt", O_CREAT | O_TRUNC | O_RDWR, 0777);
	close(1);
	dup(f);

	int n = 0;
	while(read(pd2[0], &n, sizeof(n)) > 0)
	{
		if (n > 10)
		{
			printf("%d\n", n);
		}
	}	
	
	close(pd1[0]);
	close(pd2[1]);

	return 0;
}
