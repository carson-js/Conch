#include "shell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtins.h"


void execute(char **args) {
    if (!check_builtins(args)) {
        return;
    }
    pid_t pid = fork();
    if (pid == 0) {
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else {
        waitpid(pid, NULL, 0);
    }
}


