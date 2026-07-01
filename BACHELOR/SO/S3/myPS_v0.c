#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

void error_y_exit(char *msg,int exit_status) {
perror(msg);
exit(exit_status);
}

int main (int argc,char *argv[]) {
    int pid;
    char buffer[20];
    char variable_global = 'A';

    pid = fork ();
    switch (pid) {

    case 0:
      sprintf (buffer, "HIJO: Soy el proceso %d\n", getpid ());
      write (1, buffer, strlen (buffer));


      sprintf (buffer, "HIJO:La variable_global vale %c\n",
               variable_global);
      write (1, buffer, strlen (buffer));
      while(1);


      exit (0);

    case -1:
      error_y_exit("Error en fork",1);
      break;

    default:
      sprintf (buffer, "PADRE: Soy el proceso %d\n", getpid ());
      write (1, buffer, strlen (buffer));
      while(1);
    }
  return 0;
}
