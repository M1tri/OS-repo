#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		printf("usage ./dete N\n");
		return -1;
	}
	
	int N = atoi(argv[1]);
	
	return N;
}
