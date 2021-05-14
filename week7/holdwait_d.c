#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t L1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t L2 = PTHREAD_MUTEX_INITIALIZER;
int t1 = 0;
int t2 = 0;

void *thread1(void *arg) {
    printf("t1: begin\n");
    printf("t1: try to acquire L1...\n");
    pthread_mutex_lock(&L1);
    t1++;
    printf("t1: L1 acquired\n");
    printf("t1: try to acquire L2...\n");
    if (t1 > 0) {
        pthread_mutex_unlock(&L1);
        t1--;
        pthread_mutex_lock(&L2);
        printf("t1: L2 acquired\n");
        pthread_mutex_unlock(&L2);
    }
    return NULL;
}

void *thread2(void *arg) {
    printf("                           t2: begin\n");
    printf("                           t2: try to acquire L2...\n");
    pthread_mutex_lock(&L2);
    t2++;
    printf("                           t2: L2 acquired\n");
    printf("                           t2: try to acquire L1...\n");
    if (t2 > 0) { 
        pthread_mutex_unlock(&L2); 
        t2--;
        pthread_mutex_lock(&L1);
        printf("                           t2: L1 acquired\n");
        pthread_mutex_unlock(&L1);
    }
    return NULL;
}

int main(int argc, char *argv[]) {                    
    pthread_t p1, p2;
    printf("main: begin\n");
    pthread_create(&p1, NULL, thread1, NULL); 
    pthread_create(&p2, NULL, thread2, NULL);
    // join waits for the threads to finish
    pthread_join(p1, NULL); 
    pthread_join(p2, NULL); 
    printf("main: end\n");
    return 0;
}
