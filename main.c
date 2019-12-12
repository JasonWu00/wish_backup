#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "parse.h"

int main() {
  printf("Opening shell.\n");
  printf("This shell can only take in up to 6 tokens in a single line.\n");
  printf("If you enter a nonexistent command, the shell will not execute it.\n");
  printf("Type \"exit\" to close the shell.\n");
  char input[100];
  char ** output;
  int parentPID = getpid();
  printf("WISH > ");

  while (1) {//as long as "exit" isn't entered
    fgets(input, 100, stdin);
    char *position;
    if ((position = strchr(input, '\n')) != NULL) {
      *position = '\0';
    }
    //gets input and replaces newline with null

    int numCommands;
    char *inptr = input;//pointer to input string
    char *commandArray[100];
    if(strchr(input,';') != NULL) {//check if semicolon in input
      char *indcmd;
      int q = 0;
      while((indcmd = strsep(&inptr,";")) != NULL) {
        commandArray[q] = indcmd;
        q++;
      }
      numCommands = q;
    }
    else {
      commandArray[0] = inptr;
      numCommands = 1;
    }

    char cd[3] = "cd";
    char leave[5] = "exit";
    char lessthan = "<";
    char morethan = ">";

    const char *cd_p = &cd;
    const char *leave_p = &leave;
    const char *less_p = &lessthan;
    const char *more_p = &morethan;
    for(int q = 0; q < numCommands; q++) {//for every command entered

	    char * pointer = commandArray[q];
      char backup[100];
      strcpy(backup, commandArray);
      struct parse_output outstruct;
      outstruct = parse_args(input);
      outstruct.lastToken--;
      //int has_greater = strchr(outstruct.output[outstruct.lastToken-1], ">");//has a ">"
      //int has_lessthan = strchr(outstruct.output[outstruct.lastToken-1], "<");//has a "<"

      printf("DEBUG: your cmd: %s, last_token: %i\n", commandArray[q], outstruct.lastToken);
      //printf("Command has > sign: %i, 0 if DNE\n", strchr(outstruct.output, morethan) != NULL);
      //printf("DEBUG: %s\n", backup[q]);
      //commented out printf that caused segfault
      if (strstr(commandArray[q], cd_p) != NULL) {//input command has a "cd" in it
        chdir(outstruct.output[1]);
        printf("\nWISH > ");
      }
      else if (strstr(commandArray[q], leave_p) != NULL) {//input command is "exit"
        printf("\nWISH > Exiting shell\nThank you for visiting! Come again soon!\n\n");
        exit(0);
      }
      else if (strchr(commandArray[q], morethan) != NULL) {//has a ">" or a "<"
        printf("DEBUG: value of last token: %s\n", outstruct.output[outstruct.lastToken]);
        int fd_redirectedFile = open(outstruct.output[outstruct.lastToken], O_RDWR);//to see if file exists
        int new_fd_stdout = dup(1);
        int new_fd_stding = dup(0);

        if (fd_redirectedFile == -1) {//if no such file
          printf("DEBUG: file DNE\n");
          printf("DEBUG: fd_redir has this value: %i\n", fd_redirectedFile);
          //create a file
          fd_redirectedFile = open(outstruct.output[outstruct.lastToken], O_RDWR | O_CREAT);
          //redirection below
          //dup2()
          exit(0);
        }
        else {//file exists, proceed with redirection
          printf("DEBUG: file exists\n");
          printf("DEBUG: fd_redir has this value: %i\n", fd_redirectedFile);
          exit(0);
        }
      }
      else {
        run_cmds(outstruct, parentPID);
      }
    }
    printf("\nWISH > ");
  }
}
