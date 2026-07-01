#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    char buff[256];
    int num1 = 0;
    int num2 = 4;
    int fd[2];
    int ret;
    pipe(fd);
    
    ret = fork();
    if (ret == 0) {
        close(fd[1]);
        close(1);
        dup2(0, fd[0]);
        while (read(0, &num1, sizeof(int)) > 0);
        close(fd[0]);
        sprintf(buff, "%d\n", num1);
        write(2, buff, strlen(buff));
        exit(1);
    }
    else {
        close(fd[0]);
        close(0);
        dup2(1, fd[1]);
        write(1, &num2, sizeof(int));
        close(fd[1]);
        waitpid(-1, NULL, 0);
    }
}
