#include <stdio.h>
#include <string.h>

int main(void){
    while(true){
        char input[100];
        char *argv[100];
        int argc = 0;
        printf("conch> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        char *token = strtok(input, " ");
        for (int i = 0; token != NULL; i++) {
            if (*token == '\n') break;
            if (token[strlen(token) - 1] == '\n') token[strlen(token) - 1] = '\0';
            argv[i] = token;
            ++argc;
            token = strtok(NULL, " ");
        }
        for (int i = 0; i<argc; i++) {
            printf("%s\n", argv[i]);
        }
    }
    return 0;
}
