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
    char buff[64];
    int ret, status, sal;
    int num = atoi(argv[1]);
    sprintf(buff, "%s\n", argv[2]);

    for (int i = 0; i < num; ++i) {
        ret = fork();
        if (ret == 0) {
            if (execlp("./subp1","./subp1", buff, NULL) < 0) error("execlp");
        }
        else {
            waitpid(-1, &status, 0);
            sal = WEXITSTATUS(status);
            sprintf(buff, "el total es: %d\n", sal);
            write(1, buff, strlen(buff));
        }
        sprintf(buff, "%d\n", sal);
    }
}
