#include <unistd.h>
#include <string.h>
#include <stdio.h>

int
main ()
{
  int numero = 10562;
  int fd;
  char buff[64];
  sprintf(buff, "%d\n", numero);
  write (1, buff, strlen(buff));

}
