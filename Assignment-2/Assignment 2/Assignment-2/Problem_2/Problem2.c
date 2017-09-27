/**
 *  @author Thomas Han
 *  @title operating systems hw2 problem_2
 *  @description this takes words from args and decides which one is palindrome which one is not.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int main (int argc, const char * argv[]) {

	int inputNum = 0;


	printf("input n:\n");
	scanf("%d", &inputNum);

	while (inputNum > 100) {
		printf("Input cannot be greater than 100... please try again\n");
		scanf("%d", &inputNum);
	}

	char * strArr[inputNum];

	for(int i = 0; i < inputNum; i++) {
		strArr[i] = (char *)malloc(1025 * sizeof(char));
		scanf("%s", strArr[i]);
		while(strlen(strArr[i]) > 1024) {
			printf("word longer than 1024, try again...\n");
			scanf("%s", strArr[i]);
		}
	}



    for(int j = 0; j < inputNum; j++) {

        int palindromeFlag = 1;

        // convert all the input lower case, and have them in a different char array.
        // also make sure all the inputs are less than 1024 char.

        int strLen = strlen(strArr[j]);

        char lowerCasedInput[strLen];
        for(int i = 0; i < strLen; i++) {
            lowerCasedInput[i] = (char)(tolower(strArr[j][i]));
        }
        lowerCasedInput[strLen] = '\0';

        // loop through each lowerCasedInput and print out "PALINDROME" OR "NOT PALINDROME"

        char reverseStr[strLen];
        for(int i = strLen; i > 0; i--) {
            reverseStr[i - 1] = (char)lowerCasedInput[strLen - i];
        }

        for(int i = 0; i < strLen; i++) {
            if(lowerCasedInput[i] != reverseStr[i]) {
                palindromeFlag = 0;
            }
        }

        if(palindromeFlag == 0) printf("NOT PALINDROME\n");
        else printf("PALINDROME\n");
		free(strArr[j]);
    }
    return 0;
}
