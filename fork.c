#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main(){
 pid_t pid;
 
 pid_t parent_pid = getpid();
 printf("Parent pid:%d\n",parent_pid);
 
 pid =fork();
 
 if(pid<0){
 perror("fork");
 return 0;
 }
 else if(pid==0){
 pid_t child_pid = getpid();
 printf("Child pid:%d\n",child_pid);
 printf("child process executed\n");
 }
 else{
 printf("parent process executes");
 }
 return 0;
 }
 
