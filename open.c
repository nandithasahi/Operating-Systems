#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>

int main(){
 int fd;
 fd = open("tfghjkkj.txt", O_CREAT|O_RDWR|O_TRUNC,0666);
 if(fd==-1){
 perror("open");
 return 1;
 }
 if(close(fd)==-1){
 perror("close");
 return 1;}
 return 0;
 }
 
