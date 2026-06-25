#include "shell.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#define TOKEN_DELIM ": "

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);
  char command[1024];
  char **args;

  while (1) {
    printf("$ ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0';

    args = split_text(command);

    if (strcmp(args[0], "exit") == 0) {
      exit(0);
    } else if (strcmp(args[0], "echo") == 0) {
        int i = 1;
        while(args[i] != NULL){
            printf("%s",args[i]);
            if(args[i+1] != NULL){
                printf(" ");
            }
            ++i;
        }
        printf("\n");
    } else if (strcmp(args[0], "type") == 0){
        check_command(args[1]);
    } else if (strcmp(args[0], "pwd") == 0){
        pwd();
    } else {
        if(verify_command(args[0])){
            run_command(args);
        } else {
            printf("%s: command not found\n",args[0]);
        }
    }

    free(args);
}
return 0;
}
