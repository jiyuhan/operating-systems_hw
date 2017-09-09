#include <stdio.h>

int main (int argc, char * argv[]) {
   FILE *f = fopen(argv[1], "r");
   int fileSize = 0;
   unsigned char buffer;

   if( f == NULL )  {
      perror ("Error opening file");
      return(-1);
   }

   while(fread(&buffer, 1, 1, f) == 1) {
       fileSize++;
   }
   printf("%d\n", fileSize);

   return 0;
}
