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


union semun
{
	int val;
	struct sem_ids* buf;
	ushort* array;
};

int main(int argc, char** argv)
{
	int mut_id, procA_id, procB_id;

	union semun semopts;

	char linija[20];

	FILE* prvi;
	FILE* drugi;
	FILE* zbir;

	struct sembuf sem_lock = {0, -1, 0};
	struct sembuf sem_unlock = {0, 1, 0};
	
	mut_id = semget((key_t)MUTEX_KEY, 1, 0666 | IPC_CREAT);
	procA_id = semget((key_t)PROCA_KEY, 1, 0666 | IPC_CREAT);
	procB_id = semget((key_t)PROCB_KEY, 1, 0666 | IPC_CREAT);

	// Inicijalizujemo mutex na 1 da bude otkljucan
	semopts.val = 1;
	semctl(mut_id, 0, SETVAL, semopts);

	// Inicijalizujemo semafor procesa A na jedan da bi on prvi citao i upisao
	semopts.val = 1;
	semctl(procA_id, 0, SETVAL, semopts);

	// Inicijalizujemo semafor procesa B na 0 jer on mora da ceka 
	semopts.val = 0;
	semctl(procB_id, 0, SETVAL, semopts);

	if (fork() == 0)
	{
		// dete odnosno proces A
	
		prvi = fopen("prvi.txt", "r");

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
		exit(0);
	}
	else
	{
	
		drugi = fopen("drugi.txt", "r");

		while(!feof(drugi))
		{
			fgets(linija, 20, drugi);

			semop(procB_id, &sem_lock, 1);
			semop(mut_id, &sem_lock, 1);

			zbir = fopen("zbir.txt", "a");
			fprintf(zbir, "%s", linija);
			fclose(zbir);

			semop(procA_id, &sem_unlock, 1);
			semop(mut_id, &sem_unlock, 1);
		}
		fclose(drugi);

		wait(NULL);
		semctl(mut_id, 0, IPC_RMID, 0);
		semctl(procA_id, 0, IPC_RMID, 0);
		semctl(procB_id, 0, IPC_RMID, 0);
	}

	return 0;
}
