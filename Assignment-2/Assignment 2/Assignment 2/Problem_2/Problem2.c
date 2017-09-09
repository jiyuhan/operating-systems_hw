/**
 *  @author Thomas Han
 *  @title operating systems hw2 problem_2
 *  @description this takes words from args and decides which one is palindrome which one is not.
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main (int argc, const char * argv[]) {

    for(int j = 1; j < argc; j++) {

        int palindromeFlag = 1;

        // convert all the input lower case, and have them in a different char array.
        // also make sure all the inputs are less than 1024 char.

        // char *lowerCasedInput[argc];
        if(argc > 101) {
            printf("EROOR: too many arguments. make sure there are no more than 100 inputs.\n");
            return -1;
        }

        int strLen = strlen(argv[j]);

        if(strLen > 1024) {
            printf("ERROR: word too long, make sure the word not exceeding 1024 characters.\n");
            return -1;
        }
        char lowerCasedInput[strLen];
        for(int i = 0; i < strLen; i++) {
            lowerCasedInput[i] = (char)(tolower(argv[j][i]));
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
    }
    return 0;
}
