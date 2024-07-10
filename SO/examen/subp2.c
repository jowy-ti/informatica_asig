#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int num = atoi(argv[1]);
    num = num*2;
    write(1, &num, sizeof(int));
    exit(num);
}
