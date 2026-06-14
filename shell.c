#include "shell.h"

#include <fcntl.h>
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
    if (!pipe_check(args)) {
        return;
    }
    pid_t pid = fork();
    if (pid == 0) {
        if (redirect_check(args) == -1) {
            perror("error opening file");
            exit(1);
        }
        redirect_check(args);
        execvp(args[0], args);
        perror("execvp failed");
        exit(1);
    } else {
        waitpid(pid, NULL, 0);
    }
}

int redirect_check(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        if (!strcmp(args[i], ">")) {
            args[i] = (char *) NULL;
            int fd = open(args[i+1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if (fd == -1) { return -1; }
            dup2(fd, 1);
            close(fd);
            break;
        }
        if (!strcmp(args[i], "<")) {
            args[i] = (char *) NULL;
            int fd = open(args[i+1], O_RDONLY);
            if (fd == -1) { return -1; }
            dup2(fd, 0);
            close(fd);
            break;
        }
    }
    return 1;
}

int pipe_check(char **args) {
    for (int i = 0; args[i] != NULL; i++) {
        if (!strcmp(args[i], "|")) {
            return pipeline(args, i);
        }
    }
    return 1;
}

int pipeline(char **args, int i) {
    // call pipe_check to check for more pipes
    
    // split args

    // create pipes

    // fork and execute

    return 0;
}