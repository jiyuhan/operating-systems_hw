#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*TODO: get rid of optional white spaces and return a clean command sting */
void optionalWhiteSpace(char * input) {

}

int main (int argc, char * argv[]) {
    char scanfBuffer [256];
    char cwd[1024];
    while(1) {
        printf("mysh> ");
        scanf("%s", scanfBuffer);

        /*TODO: implement pwd  */
        if(strcmp(scanfBuffer, "pwd") == 0) {
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                fprintf(stdout, "%s\n", cwd);
            }
            else {
                perror("getcwd() error");
            }
        }

        /*TODO: implement "cd": goto HOME */
        if(strcmp(scanfBuffer, "cd") == 0) {

        }

        /*TODO: implement "cd dir" goto a directory, check if exists then move */
        if(strcmp(scanfBuffer, "cd dir") == 0) {

        }

        /*TODO: implement "cd " basic ls but with only directories */
        if(strcmp(scanfBuffer, "show-dirs") == 0) {

        }

        /*TODO: implement "cd -" this shows all the files in this directory */
        if(strcmp(scanfBuffer, "show-files") == 0) {

        }

        /*TODO: implement "cd -" this makes a new directory */
        if(strcmp(scanfBuffer, "mkdir $name") == 0) {

        }

        /*TODO: implement "touch $file-name", this functin will generate a new file under the current directory */
        if(strcmp(scanfBuffer, "touch $file-name") == 0) {

        }

        /*TODO: implement "clear" */
        if(strcmp(scanfBuffer, "clear") == 0) {

        }

        /*TODO: implement "exit" */
        if(strcmp(scanfBuffer, "exit") == 0) {

        }
    }



    return 0;
}
