// dete odnosno proces A
	
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/wait.h>

#define MUTEX_KEY 1
#define PROCA_KEY 2
#define PROCB_KEY 3

int main(int argc, char** argv)
{
	int mut_id = semget((key_t)MUTEX_KEY, 1, 0666);
	int procA_id = semget((key_t)PROCA_KEY, 1, 0666);
	int procB_id = semget((key_t)PROCB_KEY, 1, 0666);
	
	char linija[20];
	
	struct sembuf sem_lock = {0, -1, 0};
	struct sembuf sem_unlock = {0, 1, 0};

	FILE* prvi;
	prvi = fopen("prvi.txt", "r");

	FILE* zbir;
	while(!feof(prvi))
	{
		fgets(linija, 20, prvi);

		semop(procA_id, &sem_lock, 1);
		semop(mut_id, &sem_lock, 1);

		zbir = fopen("zbir.txt", "a");
		fprintf(zbir, "%s", linija);
		fclose(zbir);

		semop(procB_id, &sem_unlock, 1);
		semop(mut_id, &sem_unlock, 1);
	}
	fclose(prvi);

	return 0;
}
