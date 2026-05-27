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
        input[strlen(input)-1] = '\0';
        char **args = parse_input(input);
        execute(args);
        free(args);
    }
    return 0;
}
