#pragma once

void execute(char **args);
int redirect_check(char **args);
int pipe_check(char **args);
int pipeline(char **args, const int *pipe_count);