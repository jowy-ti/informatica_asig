#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char buf[256];
    char buf2[256];
	int w;
	w = open("salida.txt", O_RDWR);
    lseek(w,-1, SEEK_END);
    read(w, buf, sizeof(char));
    lseek(w,-1, SEEK_CUR);
	sprintf(buf2,"X");
	write(w, buf, strlen(buf));
    write(w, buf2, strlen(buf2));
}
