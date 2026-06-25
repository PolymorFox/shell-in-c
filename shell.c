#include "shell.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define TOKEN_DELIM ": "
#define BUFSIZE 10

void pwd(){
    char *pwd = getenv("PWD");
    printf("%s\n",pwd);
}

void run_command(char **args){
    pid_t pid = fork();
    if(pid < 0){
        perror("Failed to fork!");
        exit(1);
    } else if (pid == 0){
        execvp(args[0], args);
    } else {
        wait(NULL);
    }
}

bool verify_command(char *command) {
  char *path = strdup(getenv("PATH"));
  char *dir = strtok(path, TOKEN_DELIM);
  while (dir != NULL) {
    int max_len = strlen(dir) + 2 + strlen(command);
    char fpath[max_len];
    snprintf(fpath, max_len, "%s/%s", dir, command);
    if (access(fpath, X_OK) == 0) {
        free(path);
      return true;
    }
    dir = strtok(NULL, TOKEN_DELIM);
  }
  free(path);
  return false;
}

bool is_builtin(char *command){
    if(strcmp(command, "type") == 0 ||strcmp(command, "exit") == 0 || strcmp(command, "echo") == 0 || strcmp(command, "pwd") == 0){
        return true;
    }
    return false;
}

void check_command(char *command) {
  if(is_builtin(command)){
      printf("%s is a shell builtin\n", command);
      return;
  }
  char *path = strdup(getenv("PATH"));
  char *dir = strtok(path, ":");
  while (dir != NULL) {
    int max_len = strlen(dir) + 2 + strlen(command);
    char fpath[max_len];
    snprintf(fpath, max_len, "%s/%s", dir, command);
    if (access(fpath, X_OK) == 0) {
      printf("%s is %s\n", command, fpath);
      free(path);
      return;
    }
    dir = strtok(NULL, ":");
  }
  printf("%s: not found\n", command);
  free(path);
}



char **split_text(char *text){
    int bufsize = BUFSIZE;
    char *token = strtok(text, TOKEN_DELIM);
    int position = 0;
    char **args = (char**)malloc(sizeof(char*)*bufsize);
    args[position] = token;
    while(token != NULL){
        ++position;
        if(position >= bufsize){
            bufsize+=bufsize;
            args = realloc(args, sizeof(char*)*bufsize);
        }
        token = strtok(NULL, TOKEN_DELIM);
        args[position] = token;
    }
    args[position] = NULL;
    return args;
}
