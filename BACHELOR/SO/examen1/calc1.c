#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

void exit_good(int wat, int *pid_t, int num_hij) {
    char buff[128];
    sprintf(buff, "%d ended correctly\n", wat);
    write (2, buff, strlen(buff));
    for (int j = 0; j < num_hij; ++j) {
        kill(pid_t[j], SIGKILL);
    }
}

void exit_bad(int wat) {
    char buff[128];
    sprintf(buff, "%d ha finalizado por un signal no tratado\n", wat);
    write (2, buff, strlen(buff));
}

int main(int argc, char *argv[]) {
    if (argc != 3) usage();
    char buff[128];
    int num_hij = atoi(argv[1]);
    int pid, status, wat;
    int pid_t[num_hij];
    int fin_hijos = 0;
    for (int i = 0; i < num_hij && fin_hijos == 0; ++i) {
        if ((pid = fork()) < 0) error("fork");
        if (pid == 0) {
            pid_t[i] = getpid();
            execlp("./hijo1", "./hijo1", argv[2], NULL);
        }
        wat = waitpid(-1, &status, WNOHANG);
        if (wat > 0) {
            if (WIFEXITED(status)) {
                exit_good(wat, pid_t, num_hij);
                fin_hijos = 1;
            }
            else exit_bad(wat);
        }
    }
    while ((wat = waitpid(-1, &status, 0)) > 0) {
        if (WIFEXITED(status)) {
            exit_good(wat, pid_t, num_hij);
            fin_hijos = 1;
        }
        else exit_bad(wat);
    }
    if (fin_hijos == 0) {
        sprintf(buff, "Incalculable\n");
        write (2, buff, strlen(buff));
    }
}
