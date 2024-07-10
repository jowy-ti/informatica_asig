#include <stdio.h>
#include <unistd.h>
#include <string.h>

int esNumero(char *str) { 
    int const MAX_SIZE = 8;
    if (str == NULL) return 0;
    if (*str == '-') ++str;
    for (int i = 0; str[i] != '\0'; i++) {
        if (!(str[i] >= '0' && str[i] <= '9') || (i >= MAX_SIZE)) return 0;
    }
    return 1;
}

int main(int argc, char *argv[]) {
    char buf[50];
    for (int i = 0; i < argc; i++) {
        if (esNumero(argv[i]) == 1) sprintf(buf, "%s es número\n", argv[i]); 
        else sprintf(buf, "%s no es número\n", argv[i]);
        write(1, buf, strlen(buf));
    }
    return 0;
}
    
