#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void usage() {
    char buff[128];
    sprintf(buff, "Se hace así\n");
    write(1, buff, strlen(buff));
}

void error_y_exit(char *msg) {
    perror(msg);
    exit(2);
}

void klk() {
    char buff[128];
    sprintf(buff, "AAHAHAHAHAHAHHAHAH\n");
    write(1, buff, strlen(buff));
}

int main(int argc, char *argv[]) {
    char buff[128];
    int fd, pid;
    int cont = -1;
    fd = open("salida.txt", O_RDWR|O_CREAT|O_TRUNC, S_IRWXU);
    
    struct sigaction trat;
    sigset_t mask;
    trat.sa_handler = klk;
    trat.sa_flags = SA_RESTART;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) error_y_exit("sigprocmask");
    if (sigaction(SIGINT, &trat, NULL) < 0) error_y_exit("sigaction");
    
    pid = fork();
    if (pid == 0) {
        sprintf(buff, "saludos desde marte\n");
        write(fd, buff, strlen(buff));
        close(fd);
        exit(0);
    }
    else {
        if (waitpid(-1, NULL, 0) < 0) error_y_exit("waitpid");
        lseek(fd, 0, SEEK_SET);
        while((cont = read(fd, buff, sizeof(buff))) > 0) {
            write(1, buff, strlen(buff));
            sprintf(buff, "%d\n", cont);
            write(1, buff, strlen(buff));
        }
        close(fd);
    }
}
