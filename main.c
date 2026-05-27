#include <stdio.h>
#include <string.h>

int main(void){
    char input[100];
    while(true){
        printf("conch> ");
        fgets(input, sizeof(input), stdin);
        char *token = strtok(input, " ");
        while (token != NULL) {
            printf("%s\n", token);
            token = strtok(NULL, " ");
        }
    }
    return 0;
}
