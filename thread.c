#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* thread(void *arg){
 int *num = (int*)arg;
 printf("thread running:arg:%d\n",(int*)num);
 return NULL;
 }
 
 int main(){
  pthread_t thr;
  int arg =55;
  
  if(pthread_create(&thr,NULL,thread,&arg)!=0){
   perror("failed");
   return 1;
   }
   if(pthread_join(thr,NULL)!=0){
   perror("failed");
   return 1;
   }
   
   printf("finished execution\n");
   return 0;
   }
