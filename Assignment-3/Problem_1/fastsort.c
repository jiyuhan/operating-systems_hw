#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define LINE_LENGTH 100 // each line is made out of 100 bytes

void swap(unsigned int *xp, unsigned int *yp);
void swapCharPtr(char** a, char** b);
int main (int argc, char * argv[]) {

    if(argc != 5) {
        printf("Please use this format: \nfastsort -i input -o output\n");
        return 0;
    }

    //TODO:  allocate a buffer size of 100 byte first. it will be for each line. Then it will be stored into a data structure.
    // being lazy, not malloc yet...
    char buffer[101];
    struct stat statStructBuffer;
    int i = 0, j = 0, k = 0;

    stat("outfile", &statStructBuffer);

    int totalLine = statStructBuffer.st_size / 100;

    unsigned int firstFourByteArr[totalLine];
    char * restBytesArr[totalLine];

    /* checking to make sure malloc has a correct number of bytes */
    // printf("%d", LINE_LENGTH / sizeof(int) * sizeof(int));
    // int * lineBuffer = malloc(LINE_LENGTH / sizeof(int) * sizeof(int));

    int fileDescriptor = open(argv[2], O_RDONLY);
    int writeOutputDesc = open(argv[4], O_CREAT | O_WRONLY, 0755);


    if(fileDescriptor == -1) {
        fprintf(stderr, "Error retrieving/opening the file.\n");
    }

    /* read the file and split the buffer into two, first four bytes, and last 96 bytes */
    while(read(fileDescriptor, buffer, 100)) {
        buffer[100] = '\0';
        // printf("%s\n", buffer);
        // firstFourByteArr[i] = malloc(4 * sizeof(char) + 1);
        firstFourByteArr[i] |= ( buffer[0] << 24 );
        firstFourByteArr[i] |= ( buffer[1] << 16 );
        firstFourByteArr[i] |= ( buffer[2] <<  8 );
        firstFourByteArr[i] |= ( buffer[3]       );

        restBytesArr[i] = malloc((LINE_LENGTH - 4) * sizeof(char) + 1);
        for(j = 4; j < LINE_LENGTH; j++) restBytesArr[i][j - 4] = buffer[j];
        restBytesArr[i][96] = '\0';
        // printf("%x\n", restBytesArr[i]);
        // printf("%x\n", firstFourByteArr[i]);
        i++;
    }

    /* sort the first bytes, and create the outputs. Since I'm lazy and bubble sort
     * is the easiest to implement, here we go...
     */
    i = 0, j = 0;
    for (i = 0; i < totalLine; i++) {
        // Last i elements are already in place
        for (j = 0; j < totalLine - i - 1; j++) {

            if (firstFourByteArr[j] > firstFourByteArr[j + 1]) {
               swap(&firstFourByteArr[j], &firstFourByteArr[j + 1]);
               swapCharPtr(&restBytesArr[j], &restBytesArr[j + 1]);
           }
        }
    }

    // for(i = 0; i < totalLine; i++) {
    //     printf("%x: %s\n", firstFourByteArr[i], restBytesArr[i]);
    // }

    close(fileDescriptor);

    char * outputCharArr[totalLine];

    /* join two arrays after sorting*/
    for(i = 0; i < totalLine; i++) {
        /*TODO: free memory for previous 96-byte array as allocating new memory for outputCharArr */
        outputCharArr[i] = malloc(LINE_LENGTH * sizeof(char));
        for(j = 0; j < LINE_LENGTH; j++) {
            if(j < 4) {
                outputCharArr[i][j] = (firstFourByteArr[i] >> (8 * j)) & 0xff;
            }
            if(j >= 4){
                outputCharArr[i][j] = restBytesArr[i][j - 4];
            }
            // free(restBytesArr[i]);
        }
    }

    for(i = 0; i < LINE_LENGTH; i++) {
        write(writeOutputDesc, outputCharArr[i], 100);
        // free(outputCharArr[i]);
    }

    close(writeOutputDesc);
    return 0;
}

void swap(unsigned int *xp, unsigned int *yp) {
    unsigned int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void swapCharPtr(char** a, char** b) {
    char *temp = *a;
    *a = *b;
    *b = temp;
}
