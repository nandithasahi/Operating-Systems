#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>

#define BUFFER_SIZE 1024

int main(){
 int fd;
 char* message;
 ssize_t bytes_written;
 
 message = (char*)malloc(BUFFER_SIZE);
 if(message==NULL){
 perror("empty msg");
 free(message);
 return 1;
 }
 
 printf("Enter content:");
 if(fgets(message,BUFFER_SIZE, stdin) == 0){
 perror("fgets");
 free(message);
 return 1;}
 
 fd = open("example.txt",O_CREAT|O_WRONLY|O_TRUNC,0666);
 if(fd==-1){
 perror("open");
 free(message);
 return 1;
 }
 
 bytes_written = write(fd, message, strlen(message));
 if(bytes_written ==-1){
 perror("write");
 free(message);
 return 1;
 }
 
 printf("wrote into file");
 
 close(fd);
 free(message);
 return 0;
 } 

