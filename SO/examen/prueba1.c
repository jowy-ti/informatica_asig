#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buff[256];
    int num1;
    int num2 = 5;
    int fd[2];
    int ret;
    pipe(fd);
    
    ret = fork();
    if (ret == 0) {
        close(fd[1]);
        dup2(0, fd[0]);
        read(0, &num1, sizeof(int));
        sprintf(buff, "%d\n", num1);
        write(1, buff, strlen(buff));
        close(fd[0]);
    }
    else {
        close(fd[0]);
        dup2(2, fd[1]);
        write(2, &num2, sizeof(int));
        waitpid(-1, NULL, 0);
        close(fd[1]);
    }
}
