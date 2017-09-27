#include <stdio.h>

int main (int argc, char * argv[]) {
    FILE *f = fopen(argv[1], "r");
    int buffer;
    int indicatorFlag = 0;
    // START = 0, INDICATOR_LOADED = 1, first_loaded = 2, second_loaded = 3
    int indicator = 0;
    int n_one = 0;
    int n_two = 0;

    if( f == NULL )  {
       perror ("Error opening file");
       return(-1);
    }

    while(fread(&buffer, 4, 1, f) == 1) {
        switch(indicatorFlag) {
          case 0:
            indicator = buffer;
            indicatorFlag = 1;
            break;
          case 1:
            n_one = buffer;
            indicatorFlag = 2;
            break;
          case 2:
            n_two = buffer;
            printf("%d\n", n_one + n_two);
            if(indicator != 0) {
                indicatorFlag = 1;
                indicator--;
            }
            break;

        }
    }

    return 0;
}
