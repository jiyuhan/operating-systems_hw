#include <stdio.h>
#include <stdlib.h>
int main (void) {
    int testCaseNum = 0;
    int inputHolder = 0;
    scanf("%d", &testCaseNum);
    int * data[testCaseNum];
    int sizeOfEach[testCaseNum];
    for(int i = 0; i < testCaseNum; i++) {
        scanf("%d", &inputHolder);
        data[i] = malloc(inputHolder * sizeof(int));
        sizeOfEach[i] = inputHolder;
        for(int j = 0; j < inputHolder; j++) {
            scanf("%d", &data[i][j]);
        }

        // sorting each input
        for (int k = 0; k < inputHolder; k++) {
            for (int j = k + 1; j < inputHolder; j++) {
                if (data[i][k] > data[i][j]) {
                    int a =  data[i][k];
                    data[i][k] = data[i][j];
                    data[i][j] = a;
                }
            }
        }
    }

    for(int i = 0; i < testCaseNum; i++) {
        for(int j = 0; j < sizeOfEach[i]; j++) {
            printf("%d ", data[i][j]);
        }
        printf("\n");
    }
}
