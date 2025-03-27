#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/shm.h>

int main()
{
void *shared_memory;
char buff[100];
int shmid;
shmid=shmget((key_t)1122, 1024, 0666|IPC_CREAT);
printf("\nKey of shared memory process 2: %d", shmid);
shared_memory= shmat(shmid, NULL, 0);
printf("\nProcess attached at: %p", shared_memory);
printf("\nData read from shared memory: %s", (char*)shared_memory);
return 0;
}
