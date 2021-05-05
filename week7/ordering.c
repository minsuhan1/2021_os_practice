#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define STATE_INIT (0)

typedef struct {
    pthread_t th;
    int state;
} my_thread_t;

my_thread_t *thd;
// mutex variable
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *routine(void *arg) {
    printf("routine: begin\n");
    // problem: access thd->state 
    // before assigning my_thread_t in main()
    // -> segmentation fault

    // Wait until main thread unlocks mutex
    pthread_mutex_lock(&mutex);
    // In this moment, main thread unlocked mutex
    // thd is assigned.
    printf("routine: state is %d\n", thd->state);
    return NULL;
}

void myWaitThread(my_thread_t *p) {
    pthread_join(p->th, NULL); 
}

my_thread_t *myCreateThread(void *(*start_routine)(void *)) {
    my_thread_t *p = malloc(sizeof(my_thread_t));
    if (p == NULL) 
	    return NULL;
    p->state = STATE_INIT;
    // start_routine: function executed by &p->th
    // In this program, function 'routine' will be executed.
    // Lock mutex in main thread, 
    // then 'routine' being executed by p->th will be executed
    // after main thread unlock mutex. (p->th is waiting for mutex)
    pthread_mutex_lock(&mutex);
    pthread_create(&p->th, NULL, start_routine, NULL); 
    // turn the sleep off to avoid the fault, sometimes...
    sleep(1);
    return p;
}

int main(int argc, char *argv[]) {
    printf("ordering: begin\n");
    thd = myCreateThread(routine);
    // unlock mutex -> let 'routine' in blocked process(thd->th) starts again.
    pthread_mutex_unlock(&mutex);
    // pthread_join
    myWaitThread(thd);
    printf("ordering: end\n");
    return 0;
}
