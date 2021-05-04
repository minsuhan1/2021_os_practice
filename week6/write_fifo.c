#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#define FIFO_PATH "./fifo_temp"
#define BUF_SIZE 100

int main() {
    int cnt = 0;
    int fd;
    char buf[BUF_SIZE];

    fd = open(FIFO_PATH, O_WRONLY);
    while(1) {
        memset(buf, 0, BUF_SIZE);
        fgets(buf, BUF_SIZE, stdin);
        write(fd, buf, strlen(buf));
    }
    close(fd);
    return 0;
}
