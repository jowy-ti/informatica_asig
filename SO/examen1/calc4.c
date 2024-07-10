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

void exit_bad(int wat, int status) {
    char buff[128];
    if (WIFEXITED(status)) {
        sprintf(buff, "%d wrong execution (exit code %d)\n", wat, WEXITSTATUS(status));
        write (2, buff, strlen(buff));
    }
    else if (WIFSIGNALED(status)) {
        sprintf(buff, "%d wrong execution (signal %d:) \n", wat, WTERMSIG(status));
        write (2, buff, strlen(buff));
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) usage();
    char buff[128];
    num_hij = atoi(argv[1]);
    int status, wat, n_status;
    pidh[num_hij];
    int fin_hijos = 0;
    
    for (int i = 0; i < num_hij && fin_hijos == 0; ++i) {
        if ((pidh[i] = fork()) < 0) error("fork");
        ++cont_hijos;
        if (pidh[i] == 0) {
            execlp("./hijo1", "./hijo1", argv[2], NULL);
        }
        wat = waitpid(-1, &status, WNOHANG);
        if (wat > 0) {
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                exit_good(wat);
                fin_hijos = 1;
            }
            else exit_bad(wat, status);
        }
    }
    while ((wat = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
            exit_good(wat);
            fin_hijos = 1;
        }
        else exit_bad(wat, status);
    }
    if (fin_hijos == 0) {
        sprintf(buff, "Incalculable\n");
        write (2, buff, strlen(buff));
    }
}
