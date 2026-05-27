#include "parser.h"

#include <stdlib.h>
#include <string.h>

char **parse_input(char *input) {
    char **args = malloc(sizeof(char *) * MAX_ARGS);
    int i = 0;
    char *token = strtok(input, " ");
    for (; token != NULL && i < MAX_ARGS - 1; i++) {
        if (*token == '\n') break;
        args[i] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;
    return args;
}