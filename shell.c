#include "shell.h"

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "builtins.h"
#include "parser.h"


void execute(char **args) {
    int pipe_count = 0;
    if (!check_builtins(args)) {
        return;
    }
    pipe_count = pipe_check(args);
    if (pipe_count != 0) {
        pipeline(args, &pipe_count);
        return;
    }
    pid_t pid = fork();
    if (pid == 0) {
        if (redirect_check(args) == -1) {
            perror("error opening file");
            exit(1);
        }
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
            dup2(fd, STDOUT_FILENO);
            close(fd);
            break;
        }
        if (!strcmp(args[i], "<")) {
            args[i] = (char *) NULL;
            int fd = open(args[i+1], O_RDONLY);
            if (fd == -1) { return -1; }
            dup2(fd, STDIN_FILENO);
            close(fd);
            break;
        }
    }
    return 1;
}

int pipe_check(char **args) {
    int num = 0;
    for (int i = 0; args[i] != NULL; i++) {
        if (!strcmp(args[i], "|")) {
            num++;
            args[i] = (char *) NULL;
        }
    }
    return num;
}

void close_all_pipes(const int *pipe_count, int pipes[][2]) {
    for (int i = 0; i < *pipe_count; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }
}

void pipeline(char **args, const int *pipe_count) {
    // split args
    char ***commands = malloc(sizeof(char **) * (*pipe_count + 1));
    int j = 0;
    for (int i = 0; i < *pipe_count+1; i++) {
        int is_first = 0;
        for (; args[j] != NULL; j++) {
            if (is_first == 0) {
                commands[i] = &args[j];
                is_first = 1;
            }
        }
        ++j;
    }
    // create pipes
    int pipes[*pipe_count][2];
    for (int i = 0; i < *pipe_count; i++) {
        pipe(pipes[i]);
    }
    // fork and execute
    int pids[*pipe_count + 1];
    for (int i = 0; i <= *pipe_count; i++) {
        pid_t pid = fork();
        pids[i] = pid;
        if (pid == 0) {
            // connect pipes as child
            if (i > 0) { dup2(pipes[i - 1][0], STDIN_FILENO); }
            if (i < *pipe_count) { dup2(pipes[i][1], STDOUT_FILENO); }
            close_all_pipes(pipe_count, pipes);
            if (redirect_check(commands[i]) == -1) {
                perror("error opening file");
                exit(1);
            }
            execvp(commands[i][0], commands[i]);
            perror("execvp failed");
            exit(1);
        }
    }
    // close parent pipes
    close_all_pipes(pipe_count, pipes);
    // parent waits for children to finish
    for (int i = 0; i <= *pipe_count; i++) {
        waitpid(pids[i], NULL, 0);
    }
    free (commands);
}