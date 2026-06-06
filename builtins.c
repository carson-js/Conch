#include <stdlib.h>
#include <string.h>
#include "builtins.h"

#include <stdio.h>
#include <unistd.h>

typedef struct {
    char *name;
    int (*func)(char **args);
} Builtin;

Builtin builtins[] = {
    {"exit", builtin_exit},
    {"cd", builtin_cd},
    {"about", builtin_about},
};

int check_builtins(char **args) {
    int n = sizeof(builtins) / sizeof(builtins[0]);
    for (int i = 0; i < n; i++) {
        if (strcmp(builtins[i].name, args[0]) == 0) {
            return builtins[i].func(args);
        }
    }
    return 1;
}

int builtin_exit(char **args) { exit(0); }
int builtin_cd(char **args) {
    chdir(args[1]);
    return 0;
}
int builtin_about(char **args) {
    printf(
        "                         __  \n"
        "  _________  ____  _____/ /_ \n"
        " / ___/ __ \\/ __ \\/ ___/ __ \\\n"
        "/ /__/ /_/ / / / / /__/ / / /\n"
        "\\___/\\____/_/ /_/\\___/_/ /_/ \n"
        "                             \n"
        "Version 0.4.0\n"
        "Built in C by Carson Smith\n"
        "https://www.github.com/carson-js/conch\n"
    );
    return 0;
}