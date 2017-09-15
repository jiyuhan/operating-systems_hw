#include <stdio.h>

int main(int argc, char *argv[]) {
    int userInput = 0;
    scanf("%d", &userInput);

    for(int i = 1; i <= userInput; i++) {
        for(int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
