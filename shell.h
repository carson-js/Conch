#pragma once

void execute(char **args);
int redirect_check(char **args);
int pipe_check(char **args);
void close_all_pipes(const int *pipe_count, int pipes[][2]);
void pipeline(char **args, const int *pipe_count);