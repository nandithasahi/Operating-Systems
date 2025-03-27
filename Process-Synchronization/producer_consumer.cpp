#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int p = 0, c = 0; 

sem_t count_empty;  
sem_t count_full;   
pthread_mutex_t mutex;  

void *producer(void *arg){
    int x;
    for(int i = 1; i <= 10; i++){
        x = i;  
        sem_wait(&count_empty);  
        pthread_mutex_lock(&mutex);  //critical section
        
        buffer[p] = x;  
        printf("Produced: %d\n", x);
        p = (p + 1) % BUFFER_SIZE;  
        
        pthread_mutex_unlock(&mutex);  
        sem_post(&count_full);  
        
        sleep(1); 
    }
    return NULL;
}

void *consumer(void *arg){
    int x;
    for(int i = 1; i <= 10; i++){
        sem_wait(&count_full); 
        pthread_mutex_lock(&mutex);  
        
        x = buffer[c];  
        printf("Consumed: %d\n", x);
        c = (c + 1) % BUFFER_SIZE;  
        
        pthread_mutex_unlock(&mutex); 
        sem_post(&count_empty);  
        
        sleep(2);  
    }
    return NULL;
}

int main(){
    pthread_t pr, cs;  

    sem_init(&count_empty, 0, BUFFER_SIZE);  
    sem_init(&count_full, 0, 0);  

    
    pthread_mutex_init(&mutex, NULL);

    pthread_create(&pr, NULL, producer, NULL);
    pthread_create(&cs, NULL, consumer, NULL);

    pthread_join(pr, NULL);
    pthread_join(cs, NULL);

    pthread_mutex_destroy(&mutex);
    sem_destroy(&count_empty);
    sem_destroy(&count_full);

    return 0;
}

