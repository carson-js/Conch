#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "shell.h"

#define MAX_INPUT 1024

int main(void){
    while(1){
        char input[MAX_INPUT];
        printf("conch> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        size_t len = strlen(input);
        if (len > 0) input[len - 1] = '\0';
        char **args = parse_input(input);
        if (args[0] != NULL) execute(args);
        free(args);
    }
    return 0;
}
