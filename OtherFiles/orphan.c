#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
 pid_t pid;
 pid = fork();
 
 if(pid<0){
 perror("pid");
 exit(EXIT_FAILURE);
 }
 
 else if(pid == 0){
  printf("child process is orphaned:%d\n:",getpid());
  sleep(10);
  printf("child still alive\n");
  }
  else{
   printf("parent process running:%d\n",getpid());
   printf("parent dies\n");
   exit(EXIT_SUCCESS);
   }
   return 0;
   }
  
