#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define BUFFER_SIZE 1024

int main(){
 int fd_read,fd_write;
 char buffer[BUFFER_SIZE];
 ssize_t bytes_read;
 
 fd_read = open("hii.txt",O_RDONLY);
 if(fd_read ==-1){
 perror("cant read from file");
 return 1;
 }
 
 fd_write = open("hii2.txt",O_CREAT|O_WRONLY|O_TRUNC, 0666);
 if(fd_write == -1){
 perror("failed to write");
 close(fd_read);
 return 1;
 }
 
 while((bytes_read= read(fd_read,buffer,BUFFER_SIZE))>0){
 if(write(fd_write,buffer,bytes_read) != bytes_read){
 perror("failed to copy");
 close(fd_read);
 close(fd_write);
 return 1;
 }
 }
 
 if(bytes_read==-1){
 perror("failed");
}
else{
printf("successfully copied");
}

close(fd_read);
close(fd_write);

return 0;
}
