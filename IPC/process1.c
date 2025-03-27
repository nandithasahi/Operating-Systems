#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<string.h>

int main(){
 int shmid;
 char arr[100];
 void* shared_memory;
 
 shmid = shmget((key_t)2345,1024,0666|IPC_CREAT);
 if(shmid == -1){
 perror("shmget");
 exit(1);
 }
 
 printf("shmid:%d\n",shmid);
 
 shared_memory=shmat(shmid,NULL,0);
 if(shared_memory==(void*)-1){
 perror("shmat");
 return 1;
 }
 printf("shared memory attached at:%p\n", shared_memory);
 
 printf("enter content into file:\n");
 if(read(0,arr,100)==-1){
  perror("failed");
  return 1;
  }
  
  strcpy((char*)shared_memory,arr);
  printf("copied:%s/n",(char*)shared_memory);
  
  return 0;
  }
 
 
