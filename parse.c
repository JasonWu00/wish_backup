#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "parse.h"

struct parse_output parse_args( char * line) {
  char ** output = calloc(sizeof(char *), 20);
  //printf("test\n");
  int counter = 0;
  struct parse_output return_struct;

  while (line != NULL) {
    output[counter] = strsep(&line, " ");
    //printf("DEBUG: counter: %i\n", counter);
    counter++;
  }
  output[19] = NULL;

  return_struct.output = output;
  return_struct.lastToken = counter;

  //printf("test 2\n");
  return return_struct;
}

void run_cmds(struct parse_output outstruct, int parentPID) {
  fork();//child process will execvp and end, parent keeps running
  if (getpid() == parentPID) {
    printf("\n");
  }
  wait(NULL);
  if (getppid() == parentPID) {
    //printf("WISH > ");
    int execute_return;
    execute_return = execvp(outstruct.output[0], outstruct.output);
    if (execute_return < 0) {
      printf("Error encountered: %i (%s)\n", errno, strerror(errno));
    }
    exit(0);
  }
}
