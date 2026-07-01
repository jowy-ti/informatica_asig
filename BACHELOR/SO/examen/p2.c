#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void usage() {
    char buf[64];
    sprintf(buf,"debes de introducir 3 enteros\n");
    write(1, buf, strlen(buf));
    exit(1);
}

void error(char *msg) {
    perror(msg);
    exit(2);
}

void fin_tiempo() {
    char buff[128];
    sprintf(buff, "Tiempo límite\n");
    write(1, buff, strlen(buff));
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc != 4) usage();
    char buff[64];
    int ret, status, sal;
    int num = atoi(argv[1]);
    int sec = atoi(argv[3]);
    sprintf(buff, "%s\n", argv[2]);
    
    struct sigaction trat;
    sigset_t mask;
    trat.sa_handler = &fin_tiempo;
    trat.sa_flags = SA_RESTART;
    sigemptyset(&mask);
    sigaddset(&mask, SIGALRM);
    sigprocmask(SIG_BLOCK, &mask, NULL);
    if (sigaction(SIGALRM, &trat, NULL) < 0) error("sigaction");
    
    alarm(sec);
    sigprocmask(SIG_UNBLOCK, &mask, NULL);
    
    while(1);

    for (int i = 0; i < num; ++i) {
        ret = fork();
        if (ret == 0) {
            if (execlp("./subp1","./subp1", buff, NULL) < 0) error("execlp");
        }
        else {
            waitpid(-1, &status, 0);
            sal = WEXITSTATUS(status);
        }
        sprintf(buff, "%d\n", sal);
    }
    sprintf(buff, "el total es: %d\n", sal);
    write(1, buff, strlen(buff));
}
