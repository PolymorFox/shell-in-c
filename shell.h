#include <stdbool.h>

void pwd();

void run_command(char **args);

bool verify_command(char *command);

bool is_builtin(char *command);

void check_command(char *command);

char **split_text(char *text);
