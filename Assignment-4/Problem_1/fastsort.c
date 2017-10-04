#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
# include "sort.h"

#define LINE_LENGTH 100 // each line is made out of 100 bytes

int compareFunction (const void * a, const void * b) {
   return ((*(rec_t *)a).key - (*(rec_t *)b).key);
}


int main (int argc, char * argv[]) {

    if(argc != 5) {
        printf("Please use this format: \nfastsort -i input -o output\n");
        return 0;
    }

    struct stat statStructBuffer;
    int i = 0;

    stat(argv[2], &statStructBuffer);

    int totalLine = statStructBuffer.st_size / 100;

    int fileDescriptor = open(argv[2], O_RDONLY);

    if(fileDescriptor == -1) {
        fprintf(stderr, "Error retrieving/opening the file.\n");
    }

    int writeOutputDesc = open(argv[4], O_CREAT | O_WRONLY, 0755);

    rec_t * allRecords = (rec_t *) malloc( totalLine * sizeof(rec_t)) ;
    for(i = 0; i < totalLine; ++i){
        int rc = read(fileDescriptor, &allRecords[i], sizeof(rec_t)) ;
    }

    qsort(allRecords, totalLine, 100, compareFunction);


    for(i = 0; i < totalLine; i++) {
        write(writeOutputDesc, &allRecords[i], sizeof(rec_t));
    }

    close(fileDescriptor);
    close(writeOutputDesc);
    free(allRecords) ;
    return 0;
}
