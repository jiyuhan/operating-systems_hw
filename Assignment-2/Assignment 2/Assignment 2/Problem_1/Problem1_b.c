#include <stdio.h>

int main(int argc, char *argv[]) {
    int userInput = 0;

    if(argc > 2) {
        printf("ERROR: too many arguments. This program only takes one argument.\n");
        return -1;
    }

    sscanf(argv[1], "%d", &userInput);


    for(int i = 1; i <= userInput; i++) {
        for(int j = (userInput - i); j > 0; j--) {
            printf(" ");
        }

        for(int j = 0; j < i; j++) {
            printf("*");
        }
        printf("\n");
    }

    return 0;
}
