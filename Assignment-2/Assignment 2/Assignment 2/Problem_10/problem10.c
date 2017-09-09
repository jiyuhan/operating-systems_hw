#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_NUM_LENGTH 10000

void add_and_print(char* num1, char* num2) {
	// Implement this function.
	// Add and print the result to standard output
}

int main (int argc , char * argv []) {
	FILE *file = fopen("problem3.input","r");
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
