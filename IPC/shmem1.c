#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>

int main()
{
void *shared_memory;
char buff[100];
int shmid;
shmid=shmget((key_t)1122, 1024, 0666|IPC_CREAT);//creates shared memory with key 2345
printf("\nKey of shared memory is: %d", shmid);
shared_memory= shmat(shmid, NULL, 0);//process now attached to shared memory segment
printf("\nProcess attached at shared memory: %p", shared_memory);
read(0, buff, 100);//get input from user
strcpy(shared_memory, buff);
printf("\nYour wrote: %s", (char*)shared_memory);
return 0;
}

