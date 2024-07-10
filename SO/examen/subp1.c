#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int num = atoi(argv[1]);
    num = num*2;
    exit(num);
}
