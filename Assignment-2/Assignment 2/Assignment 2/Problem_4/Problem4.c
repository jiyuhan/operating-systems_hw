#include <stdio.h>

int main (int argc, char * argv[]) {
	int inputNum = 0;
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

	printf("MAX: %d\n", intArr[inputNum - 1]);
	printf("MIN: %d\n", intArr[0]);
    return 0;
}
