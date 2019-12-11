#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "parse.h"

char ** parse_args( char * line ) {
  char ** output = calloc(sizeof(char *), 6);
  //printf("test\n");
  int counter = 0;

  while (counter <= 1) {
    output[counter] = strsep(&line, " ");
    counter++;
  }
  output[5] = NULL;

  //printf("test 2\n");
  return output;
}



/*
void run_cmds(char * commandArray[100], int numCommands) {
    char cd[3] = "cd";
    char leave[5] = "exit";
    const char *cd_p = &cd;
    const char *leave_p = &leave;

    for(int q = 0; q < numCommands; q++) {//for every command entered

	  char * pointer = commandArray[q];
      output = parse_args(pointer);

      if (strstr(commandArray[q], cd_p) != NULL) {//input command has a "cd" in it
        chdir(output[1]);
        printf("\nWISH > ");
      }
      else if (strstr(commandArray[q], leave_p) != NULL) {//input command is "exit"
        printf("\nWISH > Exiting shell\nThank you for visiting! Come again soon!\n\n");
        exit(0);
      }
      else {
        fork();//child process will execvp and end, parent keeps running
        if (getpid() == parentPID) {
          printf("\n");
        }
        wait(NULL);
        if (getppid() == parentPID) {
          //printf("WISH > ");
          int execute_return;
          execute_return = execvp(output[0], output);
          if (execute_return < 0) {
            printf("Error encountered: %i (%s)\n", errno, strerror(errno));
          }
          exit(0);
        }
      }
}*/
