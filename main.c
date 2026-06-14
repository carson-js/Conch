#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "shell.h"

int main(void){
    while(1){
        char input[MAX_INPUT];
        printf("conch > ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        size_t len = strlen(input);
        if (len > 0) input[len - 1] = '\0';
        char **args = parse_input(input);
        if (args[0] != NULL) execute(args);
        for (int i = 0; args[i] != NULL; i++) {
            free(args[i]);
        }
        free(args);
    }
    return 0;
}
