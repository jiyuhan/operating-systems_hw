#include <stdio.h>

int getFibonacci(int nth);

int main (void) {
    int size = 0;
    scanf("%d", &size);

    int inputHolder[size];
    for(int i = 0; i < size; i++) {
        scanf("%d", &inputHolder[i]);
    }
    for(int i = 0; i < size; i++) {
        printf("%d\n", getFibonacci(inputHolder[i]));
    }
}

int getFibonacci(int nth) {
    if (nth == 0) {
        return 0;
    }
    else if (nth == 1) {
        return 1;
    }
    else {
        return(getFibonacci(nth - 1) + getFibonacci(nth - 2));
    }
}
