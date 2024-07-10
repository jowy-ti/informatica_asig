#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void usage() {
    char buf[64];
    sprintf(buf,"debes de introducir dos palabras\n");
    write(1, buf, strlen(buf));
    exit(1);
}

void error(char *msg) {
    perror(msg);
    exit(2);
}

int main(int argc, char *argv[]) {
    if (argc != 3) usage();
    int fd[2];
    char buff[256];
    int klk;
    int ret, status;
    int sal_pipe = 0;
    int sal = 0;
    int num = atoi(argv[1]);
    int std_in;
    sprintf(buff, "%s\n", argv[2]);

    if (pipe(fd) < 0) error("pipe");
    
    ret = fork();
    if (ret == 0) {
        close(fd[1]);
        dup2(fd[0], 0);
        close(fd[0]);
        for (int i = 0; i < num; ++i) {
            read(0, &klk, sizeof(int));
            sal_pipe += klk;
        }
        sprintf(buff, "El total de la pipe es: %d\n", sal_pipe);
        write(1, buff, strlen(buff));
    }
    else {
        close(fd[0]);
        dup2(1, std_in);
        dup2(fd[1], 1);
        close(fd[1]);
        for (int i = 0; i < num; ++i) {
            ret = fork();
            if (ret == 0) {
                if (execlp("./subp2","./subp2", buff,  NULL) < 0) error("execlp");
            }
            else {
                waitpid(-1, &status, 0);
                sal += WEXITSTATUS(status);
            }
            sprintf(buff, "%d\n", sal);
        }
        sprintf(buff, "el total es: %d\n", sal);
        write(std_in, buff, strlen(buff));
    }
}
