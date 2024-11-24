#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/file.h>

int main(int argc, char** argv)
{
	if (argc != 4)
	{
		printf("Neispravno pozvan program!\n");
		return -1;
	}

	int pd[2];

	pd[0] = atoi(argv[1]);
	pd[1] = atoi(argv[2]);

	close(pd[1]);
	
	FILE* f = fopen(argv[3], "wb");
	unsigned char linija[300];
	unsigned char buff;
	int count;
	int pos;

	unsigned char xor_mask;

	int kraj = 0;
	while(!kraj)
	{
		pos = 0;

		while (pos < 200)
		{
			count = read(pd[0], &buff, 1);

			if (count == 0)
			{	
				kraj = 1;
				break;
			}
			linija[pos] = buff;
			pos++;
		}		
		
		xor_mask = (unsigned char)rand();

		if (xor_mask == 0)
			xor_mask = 1;
		
		for (int i = 0; i < pos; i++)
		{
			linija[i] = linija[i] ^ xor_mask;
		}
		
		fwrite(&xor_mask, 1, 1, f);
		fwrite(linija, 1, pos, f);
	}
	fclose(f);

	close(pd[0]);

	return 0;
}
