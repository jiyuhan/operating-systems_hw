#include <stdio.h>
#include <math.h>

int main (int argc, char * argv[]) {
	int inputNum = 0;
	int sum = 0;
	scanf("%d", &inputNum);
	int intArr[inputNum];
	for(int i = 0; i < inputNum; i++) {
		scanf("%d", &intArr[i]);
	}

	for (int i = 0; i < inputNum; i++) {
        for (int j = i + 1; j < inputNum; j++) {
            if (intArr[i] > intArr[j]) {
                int a =  intArr[i];
                intArr[i] = intArr[j];
                intArr[j] = a;
            }
        }
    }

	for(int i = 0; i < inputNum; i++) {
		sum += intArr[i];
	}

	float average = (float) sum / inputNum;

	int median = (int) (inputNum - 1) / 2;

	printf("Max: %d\n", intArr[inputNum - 1]);
	printf("Min: %d\n", intArr[0]);
	printf("Average: %f\n", average);
	printf("Median: %d\n", intArr[median]);
    return 0;
}
