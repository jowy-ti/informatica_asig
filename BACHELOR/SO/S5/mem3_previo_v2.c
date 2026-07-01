#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include<unistd.h>

#define REGION_SIZE		4096

int *p;

void func() {
    char buff[100];
    sprintf (buff, "error de segmentacion\n");
    write (1, buff, strlen (buff));
    kill(getpid(), SIGKILL);
}

int
main (int argc, char *argv[])
{
  char buff[256];

  sprintf (buff, "Addresses:\n");
  write (1, buff, strlen (buff));
  sprintf (buff, "\tp: %p\n", &p);
  write (1, buff, strlen (buff));
  struct sigaction trat;
  trat.sa_handler = func;
  trat.sa_flags = SA_RESTART;
  sigaction(SIGSEGV, &trat, NULL);

  *p = 5;

  sprintf (buff, "\tp Address: %p, p value: %p, *p: %d\n", &p, p, *p);
  write (1, buff, strlen (buff));

  exit (0);

}
