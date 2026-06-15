#include "parser.h"
#include "shell.h"

#include <stdlib.h>
#include <string.h>

char **parse_input(const char *input, int *args_count) {
    char **args = malloc(sizeof(char *) * MAX_ARGS);
    int i = 0;
    int j = 0;
    int is_inside_quotes = 0;
    char tmp_token[MAX_INPUT];
    for (int k = 0; input[k] != '\0'; k++) {
        if (input[k] == ' ' && is_inside_quotes == 0) {
            if (j == 0) { continue; }
            tmp_token[j] = '\0';
            j = 0;
            args[i] = strdup(tmp_token);
            ++i;
            continue;
        }
        if (input[k] == '"') {
            if (is_inside_quotes == 0) {
                is_inside_quotes = 1;
            } else {
                is_inside_quotes = 0;
            }
            continue;
        }
        tmp_token[j] = input[k];
        ++j;
    }
    if (j != 0) {
        tmp_token[j] = '\0';
        args[i] = strdup(tmp_token);
        ++i;
    }
    args[i] = NULL;
    *args_count = i;
    return args;
}