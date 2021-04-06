#include <stdio.h>
#include <stdlib.h>     // exit
#include <unistd.h>     // getpid, fork, sleep
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int) getpid());
    int ret_fork = fork();
    if (ret_fork < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (ret_fork == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        printf("안녕\n");
    } else {
        // parent goes down this path (original process)
        sleep(2);
        printf("잘 가\n");
   }
    return 0;
}
