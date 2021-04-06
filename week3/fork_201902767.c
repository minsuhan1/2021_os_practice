#include <stdio.h>
#include <stdlib.h> // exit
#include <unistd.h> // fork, getpid

int gvar = 10;  // 전역변수
int main(int argc, char *argv[])
{
    int lvar = 20;  // 지역변수. 20으로 초기화
    printf("hello world (pid:%d)\n", (int) getpid());
    printf("[before fork] gvar: %d, lvar: %d\n", gvar, lvar);

    int ret_fork = fork();
    if (ret_fork < 0) {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (ret_fork == 0) {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int) getpid());
        lvar -= 3;
        printf("[child] gvar: %d, lvar: %d\n", gvar, lvar);
    } else {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n",
	       ret_fork, (int) getpid());
        sleep(1);   // child process에서 gvar,lvar을 변경하는 동안 sleep 
        gvar -= 3;
        printf("[parent] gvar: %d, lvar: %d\n", gvar, lvar);
    }
    return 0;
}
