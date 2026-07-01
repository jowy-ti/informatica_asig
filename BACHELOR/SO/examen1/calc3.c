#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int cont = 0;
int cont_hijos = 0;
int num_hij = 0;
int pidh[1];

void usage() {
    char buf[128];
    sprintf(buf,"debes introducir el número de hijos y nombre de fichero\n");
    write(1, buf, strlen(buf));
    exit(1);
}

void error(char *msg) {
    perror(msg);
    exit(2);
}

void exit_good(int wat) {
    char buff[128];
    sprintf(buff, "%d ended correctly\n", wat);
    write (2, buff, strlen(buff));
    for (int i = 0; i < num_hij; ++i) kill(pidh[i], SIGKILL);
}

void exit_bad(int wat) {
    char buff[128];
    sprintf(buff, "%d ha finalizado por un signal no tratado\n", wat);
    write (2, buff, strlen(buff));
}

void sigalrm() {
    char buff[128];
    ++cont;
    sprintf(buff, "%d hijos creados y %d segundos en ejecución\n", cont_hijos, cont);
    write (1, buff, strlen(buff));
    alarm(1);
}

void sigint() {
    char buff[128];
    sprintf(buff, "SIGINT\n");
    write (2, buff, strlen(buff));
    for (int i = 0; i < num_hij; ++i) kill(pidh[i], SIGKILL);
}

int main(int argc, char *argv[]) {
    if (argc != 3) usage();
    char buff[128];
    num_hij = atoi(argv[1]);
    int status, wat;
    pidh[num_hij];
    int fin_hijos = 0;
    
    struct sigaction trat;
    struct sigaction trat2;
    sigset_t mask;
    trat.sa_handler = sigint;
    trat.sa_flags = SA_RESTART;
    trat2.sa_handler = sigalrm;
    trat2.sa_flags = SA_RESTART;
    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    sigaddset(&mask, SIGALRM);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) error("siprocmask");
    if (sigaction(SIGINT,&trat , NULL) < 0) error("sigaction");
    if (sigaction(SIGALRM,&trat2 , NULL) < 0) error("sigaction");
    
    if (sigprocmask(SIG_UNBLOCK, &mask, NULL) < 0) error("siprocmask");
    alarm(1);
    
    for (int i = 0; i < num_hij && fin_hijos == 0; ++i) {
        if ((pidh[i] = fork()) < 0) error("fork");
        ++cont_hijos;
        if (pidh[i] == 0) {
            execlp("./hijo1", "./hijo1", argv[2], NULL);
        }
        wat = waitpid(-1, &status, WNOHANG);
        if (wat > 0) {
            if (WIFEXITED(status)) {
                exit_good(wat);
                fin_hijos = 1;
            }
            else exit_bad(wat);
        }
    }
    while ((wat = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            exit_good(wat);
            fin_hijos = 1;
        }
        else exit_bad(wat);
    }
    if (fin_hijos == 0) {
        sprintf(buff, "Incalculable\n");
        write (2, buff, strlen(buff));
    }
}
