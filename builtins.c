#include <stdlib.h>
#include <string.h>
#include "builtins.h"

typedef struct {
    char *name;
    int (*func)(char **args);
} Builtin;

Builtin builtins[] = {
    {"exit", builtin_exit},
};

int check_builtins(char **args) {
    for (int i = 0; i < sizeof(builtins); i++) {
        if (strcmp(builtins[i].name, args[0]) == 0) {
            builtins[i].func(args);
        }
    }
    return 0;
}

int builtin_exit(char **args) { exit(0); }