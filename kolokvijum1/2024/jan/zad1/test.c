#include <stdio.h>

int main(int argc, char** argv)
{
	char linija[100];

	FILE* f = fopen("ulaz.txt", "r");

	while (fgets(linija, 100, f) != NULL)
	{
		printf("%s", linija);
		
		if (feof(f))
		{
			printf("Kraj\n");
		}
	}

	fgets(linija, 100, f);

	if (feof(f))
	{
		printf("Kraj\n");
	}


	return 0;
}
