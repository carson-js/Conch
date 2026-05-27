#include <stdlib.h>
#include <string.h>
#include "builtins.h"
#include <unistd.h>

typedef struct {
    char *name;
    int (*func)(char **args);
} Builtin;

Builtin builtins[] = {
    {"exit", builtin_exit},
    {"cd", builtin_cd},
};

int check_builtins(char **args) {
    int n = sizeof(builtins) / sizeof(builtins[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(builtins[i].name, args[0]) == 0) {
            builtins[i].func(args);
            return 0;
        }
    }
    return 1;
}

int builtin_exit(char **args) { exit(0); }
int builtin_cd(char **args) {
    chdir(args[1]);
}