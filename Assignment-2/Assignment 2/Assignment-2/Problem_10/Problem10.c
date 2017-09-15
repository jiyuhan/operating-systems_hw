#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NUM_LENGTH 10000

void add_and_print(char* num1, char* num2) {
	// Implement this function.
	int hold = 0;
	int digitHelper = 0;

	int digit1 = 0;
	int digit2 = 0;

	int sum = 0;

	int nALength = strlen(num1);
	int nBLength = strlen(num2);
	char result[nALength + nBLength];

	if(nALength > nBLength) {
		digitHelper = nALength - nBLength;
		result[nALength] = '\0';
		for(int i = nALength - 1; i >= 0; i--) {

			digit1 = num1[i] - '0';
			digit2 = num2[i - digitHelper] - '0';

			if(digit1 == -48) {
				sum = digit2;
			}
			else if(digit2 == -48){
				sum = digit1;
			}
			else {
				sum = digit1 + digit2;
			}

			// printf("sum: %d\n", sum);

			if(sum > 9) {
				if(hold == 1) {
					result[i] = (char) (sum - 9) + '0';
				} else {
					result[i] = (char) (sum - 10) + '0';
				}
				hold = 1;
			} else {
				if(hold == 1) {
					sum++;
					if(sum > 9) {
						hold = 1;
						result[i] = (char) (sum - 10) + '0';
					} else {
						result[i] = (char) sum + '0';
						hold = 0;
					}
				} else {
					hold = 0;
					result[i] = (char) sum + '0';
				}

			}
		}
	} else {
		digitHelper = nBLength - nALength;
		result[nBLength] = '\0';
		for(int i = nBLength - 1; i >= 0; i--) {

			digit1 = num1[i - digitHelper] - '0';
			digit2 = num2[i] - '0';

			if(digit1 == -48) {
				sum = digit2;
			}
			else if(digit2 == -48){
				sum = digit1;
			}
			else {
				sum = digit1 + digit2;
			}

			// printf("sum: %d\n", sum);

			if(sum > 9) {
				if(hold == 1) {
					result[i] = (char) (sum - 9) + '0';
				} else {
					result[i] = (char) (sum - 10) + '0';
				}
				hold = 1;
			} else {
				if(hold == 1) {
					sum++;
					if(sum > 9) {
						hold = 1;
						result[i] = (char) (sum - 10) + '0';
					} else {
						result[i] = (char) sum + '0';
						hold = 0;
					}
				} else {
					hold = 0;
					result[i] = (char) sum + '0';
				}

			}
		}
	}
	printf("%s\n", result);
}

int main (int argc , char * argv []) {
	FILE *file = fopen(argv[1],"r");
	if (file == NULL) {
		printf("Input file not found.\n");
		return 1;
	}
	char num1[MAX_NUM_LENGTH];
	char num2[MAX_NUM_LENGTH];
	while(fscanf(file, "%s %s", num1, num2) == 2) {
		add_and_print(num1, num2);
	}
	fclose(file);
	return 0 ;
}
