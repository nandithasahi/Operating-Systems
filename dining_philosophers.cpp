#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define N 5
#define THINK 0
#define HUNGRY 1
#define EATING 2
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N

sem_t mutex;
sem_t chopstick[N];

int state[N];

void test(int i) {
    if(state[i] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[i] = EATING;
        printf("Philosopher %d takes chopstick %d and %d\n", i, LEFT, i);
        printf("Philosopher %d is eating\n", i);
        sem_post(&chopstick[i]);
    }
}

void chopstick_use(int i) {
    sem_wait(&mutex);
    state[i] = HUNGRY;
    printf("Philosopher %d is hungry\n", i);
    test(i);
    sem_post(&mutex);
    sem_wait(&chopstick[i]);
    sleep(1);
}

void chopstick_return(int i) {
    sem_wait(&mutex);
    state[i] = THINK;
    printf("Philosopher %d puts down chopstick %d and %d\n", i, LEFT, i);
    printf("Philosopher %d is thinking\n", i);
    test(LEFT);
    test(RIGHT);
    sem_post(&mutex);
}

void* philosopher(void *num) {
    int i = *(int*)num;
    while(1) {
        sleep(1);
        chopstick_use(i);
        sleep(1);
        chopstick_return(i);
    }
}

int main() {
    pthread_t thread_id[N];
    int philosopher_num[N];
    
    sem_init(&mutex, 0, 1);
    for(int i = 0; i < N; i++) {
        sem_init(&chopstick[i], 0, 0);
        philosopher_num[i] = i;
    }
    
    for(int i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &philosopher_num[i]);
    }
    
    for(int i = 0; i < N; i++) {
        pthread_join(thread_id[i], NULL);
    }
    
    return 0;
}

