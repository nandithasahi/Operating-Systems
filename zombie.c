#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

int main(){
 pid_t pid;
 pid = fork();
 
 if(pid<0){
 perror("pid");
 return 1;
 }
 
 if(pid==0){
 printf("child process is executed:%d\n",getpid());//child is executed but is not called, remains in zombie state.
 exit(0);
 }
 else{
  printf("parent process is running:%d\n",getpid());
  printf("parent sleeps\n");
  sleep(10);//parent is alive but doesnt call wait-child is in zombie state
  printf("child is in zombie state while parent was sleeping, parent hasnt called wait\n");
  wait(NULL);
  printf("parent calls wait, process not in zombie state\n");
  printf("parent terminated\n");
  }
  return 0;
  }
  
