#include <stdio.h>

int main (int argc, char * argv[]) {
    FILE *f = fopen(argv[1], "r");
    unsigned int buffer;

    if( f == NULL )  {
       perror ("Error opening file");
       return(-1);
    }

    while(fread(&buffer, 4, 1, f) == 1) {
        printf("%d\n", buffer);
    }

    return 0;
}
