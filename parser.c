#include "parser.h"

#include <stdlib.h>
#include <string.h>

char **parse_input(char *input) {
    char **args = malloc(sizeof(char *) * MAX_ARGS);
    char *token = strtok(input, " ");
    for (int i = 0; token != NULL; i++) {
        if (*token == '\n') break;
        args[i] = token;
        token = strtok(NULL, " ");
    }
    return args;
}