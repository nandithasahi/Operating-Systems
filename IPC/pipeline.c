#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(){
 int pipefd[2];
 char buffer[100];
 char str[100];
 
 if(pipe(pipefd)==-1){
 perror("pipefd");
 return 1;
 }
 
 printf("enter data to write into pipe:\n");
 scanf("%99s",str);
 
 ssize_t written = write(pipefd[1],str,strlen(str)+1);
 if(written == -1){
 perror("write");
 return 1;
 }
 printf("Data written:%s\n", str);
 
 ssize_t reads = read(pipefd[0],buffer,sizeof(buffer));
 if(reads == -1){
 perror("read");
 return 1;
 }
 
 printf("data read:%s\n",buffer);
 
 close(pipefd[0]);
 close(pipefd[1]);
 
 return 0;
 }
 
 
