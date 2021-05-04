#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <semaphore.h>
#include <errno.h>

#define FIFO_PATH "fifo_temp"
#define SEM_NAME "sem_pp"
#define BUF_SIZE 8
#define TURN 5


int main()
{
    const char *msg = "pong\n";
    int fd;
    int cnt;
    int score = 100;
    sem_t *p_sem;
    char buf[BUF_SIZE];

    /*
       Homework
       Fill your codes here and make the correct result.
       Refer to the included header files and given variables.
       You can complete this file from this skeleton without creating another variable,
       but also modify anything as you want.
       As long as your result is correct, it doesn't matter how you write codes.
       However, you must use fifo, named semaphore.
       And based on this file, you have to create another source for the client.
       It would be similar to this.
    */
    if((p_sem = sem_open(SEM_NAME, 0)) == SEM_FAILED) {
        perror("sem_open");
        exit(1);
    } 
    cnt = 0;
    while(++cnt <= TURN) {
        fd = open(FIFO_PATH, O_RDWR);
        memset(buf, 0, BUF_SIZE);
        int n = read(fd, buf, BUF_SIZE);
        if(n > 0) {
            printf("[opponent] : %s", buf);
        }
                
        printf("your turn!\n");
        memset(buf, 0, BUF_SIZE);
        fgets(buf, BUF_SIZE, stdin);
        if (strcmp(buf, msg)) {
            printf("wrong! -20\n");
            score -= 20;
        }
        sem_wait(p_sem);
        write(fd, buf, strlen(buf)+1);
        sem_post(p_sem);
        close(fd);
        sleep(1);
    }
    printf("Done! Your score: %d\n", score);
    return 0;
}
