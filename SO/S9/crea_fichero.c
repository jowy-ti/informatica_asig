#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
	char buf[256];
	int f;
	f = creat("salida.txt", O_CREAT|O_TRUNC|O_RDWR);
	sprintf(buf,"ABCD");
	write(f, buf, strlen(buf));
}
