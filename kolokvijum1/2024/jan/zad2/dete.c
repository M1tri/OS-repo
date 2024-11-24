#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int to_digit(char d);

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

	close(pd1[1]);
	close(pd2[0]);

	char rec[200];

	int l;
	int s;
	while (read(pd1[0], rec, 200) > 0)
	{
		l = strlen(rec);
		s = 0;
		for (int i = 0; i < l; i++)
		{
			if (rec[i] >= '0' && rec[i] <= '9')
			{
				s += to_digit(rec[i]);
			}
		}
		write(pd2[1], &s, sizeof(s));
	}

	close(pd1[0]);
	close(pd2[1]);

	return 0;
}

int to_digit(char d)
{
	switch (d)
	{
		case '0':
			return 0;
		case '1':
			return 1;
		case '2':
			return 2;
		case '3':
			return 3;
		case '4':
			return 4;
		case '5':
			return 5;
		case '6':
			return 6;
		case '7':
			return 7;
		case '8':
			return 8;
		case '9':
			return 9;
		default:
			return 0;		
	
	}
}
