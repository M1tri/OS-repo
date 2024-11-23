#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char** argv)
{
	int pd1[2]; // od roditelja do prvo dete
	int pd2[2]; // od prvo dete do drugo dete

	if (pipe(pd1) < 0)
	{
		printf("Nuepsesno kreiranje prvog datavoda\n");
		return -1;
	}

	if (pipe(pd2) < 0)
	{
		printf("Nuepsesno kreiranje drugog datavoda\n");
		return -2;
	}

	
	char str_pd1[2][100];
	char str_pd2[2][100];

	sprintf(str_pd1[0], "%d", pd1[0]);
	sprintf(str_pd1[1], "%d", pd1[1]);

	sprintf(str_pd2[0], "%d", pd2[0]);
	sprintf(str_pd2[1], "%d", pd2[1]);

	if (fork() == 0) // prvo dete
	{
		if (execl("./prvo", "./prvo", str_pd1[0], str_pd1[1], str_pd2[0], str_pd2[1], NULL) < 0)
		{
			printf("Nesupesno kreiranje prvog deteta\n");
			return -3;
		}	
	}
	
	if (fork() == 0)
	{
		if (execl("./drugo", "./drugo", str_pd1[0], str_pd1[1], str_pd2[0], str_pd2[1], NULL) < 0)
		{
			printf("Neuspesno kreiranje drugog deteta\n");
			return -4;
		}	
	}
	
	close(pd1[0]); // pisemo

	// ovo ne koristimo
	close(pd2[0]);
	close(pd2[1]);

	char recenica[100];
	int kraj = 0;

	do
	{
		fgets(recenica, 100, stdin); // <3
				
		if (strcmp(recenica, "kraj\n") != 0)
		{
			printf("Roditelj: %s", recenica);
		}
		else
		{
			kraj = 1;
		}

		write(pd1[1], recenica, strlen(recenica) + 1);
	}
	while(!kraj); 

	wait(NULL); 
	wait(NULL); 
	
	close(pd1[1]); // umiremo pa nam ne treba vise

	return 0;
}
