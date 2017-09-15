#include <stdio.h>

int main (int argc, char * argv[]) {
    FILE *f = fopen(argv[1], "r");

    char line[256];
    int indicatorIsRead = 0;
    int indicator = 0;
    int firstInt = 0;
    int secondInt = 1;
    int sum = 0;

    if( f == NULL )  {
       perror ("Error opening file");
       return(-1);
    }

    FILE * fb = fopen (argv[2], "wb");
    if (fb != NULL) {
        while(fgets(line, sizeof(line), f)) {
            if(indicatorIsRead) {
                sscanf(line, "%d %d", &firstInt, &secondInt);
                sum = firstInt + secondInt;
                printf("%d\n", sum);
                fwrite (&sum, sizeof(sum), 1, fb);
            } else {
                sscanf(line, "%d", &indicator);
                indicatorIsRead = 1;
            }
        }
        fclose (fb);
    }



    return 0;
}
