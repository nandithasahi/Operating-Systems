#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>

int main(){
 int shmid;
 void *shared_memory;
 
 shmid = shmget((key_t)2345,1024,0666|IPC_CREAT);
 if(shmid==-1){
 perror("failed");
 return 1;}
 
 printf("shmid:%d\n",shmid);
 
 shared_memory = shmat(shmid,NULL,0);
 if(shared_memory==(void*)-1){
 perror("failed2");
 return 1;
 }
 printf("process attached at :%p\n",shared_memory);
 printf("data from shared memory:%s\n",(char*)shared_memory);
 
 return 0;
 }
 
