#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <curses.h>
#include <dirent.h>

#define MAX_INPUT_SIZE 512

// strtok

int main (int argc, char * argv[]) {
    // since the maximum length of input in shell should be 512B
    char scanfBuffer[MAX_INPUT_SIZE];
    char cwd[1024];
    char * command = (char *)malloc(MAX_INPUT_SIZE * sizeof(char));
    char * arg= (char *)malloc(MAX_INPUT_SIZE * sizeof(char));
    int i = 0;

    while(1) {
        printf("mysh> ");
        scanf("%[^\n]%*c", scanfBuffer);

        command = strtok (scanfBuffer, " ");
        arg = strtok (NULL, " ");

        if(strcmp(command, "pwd") == 0) {
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                fprintf(stdout, "%s\n", cwd);
            }
            else {
                perror("getcwd() error");
            }
        }

        else if(strcmp(command, "cd") == 0) {
            if(arg == NULL) {
                chdir(getenv("HOME"));
            } else {
                chdir(arg);
            }
        }

        else if(strcmp(command, "show-dirs") == 0) {
            DIR *d;
            struct dirent *dir;
            d = opendir(".");
            if (d) {
                while ((dir = readdir(d)) != NULL) {
                    if(dir->d_type == DT_DIR)
                        printf("%s\n", dir->d_name);
                }
                closedir(d);
            }
        }

        else if(strcmp(command, "show-files") == 0) {
            DIR *d;
            struct dirent *dir;
            d = opendir(".");
            if (d) {
                while ((dir = readdir(d)) != NULL) {
                    if(dir->d_type != DT_DIR)
                        printf("%s\n", dir->d_name);
                }
                closedir(d);
            }
        }

        else if(strcmp(command, "mkdir") == 0) {
            if(arg == NULL) printf("mkdir [new folder name]\n");
            else {
                char message[1024];
                strcat(message, arg);
                strcat(message, " already exists.\n");
                if(! mkdir(arg, 0755)) {}
                else fprintf(stderr, strcat(arg, " already exists.\n"));
            }
        }

        else if(strcmp(command, "touch") == 0) {
            FILE* file_ptr = fopen(arg, "w");
            fclose(file_ptr);
        }

        else if(strcmp(command, "clear") == 0) {
            system("clear");
        }

        else if(strcmp(command, "exit") == 0) {
            exit(1);
        }

        else {
            printf("unrecognized command\n");
        }
    }
    return 0;
}
