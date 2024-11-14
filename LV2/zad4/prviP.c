#include <stdio.h>

int main(int argc, char** argv)
{
	if (argc < 2)
	{
		printf("Retarde daj argumenti\n");
		return -1;
	}

	for (int i = 1; i < argc; i++)
	{
		printf("%s\n", argv[i]);
	}

	return 0;
}
