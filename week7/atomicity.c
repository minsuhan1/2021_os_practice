#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>

typedef struct {
    int pid;
} proc_t;

typedef struct {
    proc_t *proc_info;
} thread_info_t; 

proc_t p;
thread_info_t *thd;
// add semaphore variable
// initial key value is 0 
// in order to execute thread2 first.
int key = 0;
sem_t sem;

void *thread1(void *arg); 
void *thread2(void *arg); 

int main(int argc, char *argv[]) {
    thread_info_t t; 
    p.pid = 100; 
    t.proc_info = &p; 
    thd = &t;
    // sem init
    sem_init(&sem, 0, key); 

    pthread_t p1, p2;
    printf("main: begin\n");
    pthread_create(&p1, NULL, thread1, NULL); 
    pthread_create(&p2, NULL, thread2, NULL);
    // join waits for the threads to finish
    pthread_join(p1, NULL); 
    pthread_join(p2, NULL); 
    printf("main: end\n");
    // sem destroy
    sem_destroy(&sem);
    return 0;
}

void *thread1(void *arg) {
    sem_wait(&sem);
    printf("t1: before check\n");
    sleep(1);
    
    if (thd->proc_info) {
        printf("t1: after check\n");
        sleep(2);
        printf("t1: use!\n");
        printf("%d\n", thd->proc_info->pid);
    }
    sem_post(&sem);
    return NULL;
}

void *thread2(void *arg) {
    printf("                 t2: begin\n");
    sem_post(&sem);
    sleep(1);

    sleep(1); // change to 5 to make the code "work"...
    sem_wait(&sem);
    printf("                 t2: set to NULL\n");
    thd->proc_info = NULL;
    return NULL;
}
