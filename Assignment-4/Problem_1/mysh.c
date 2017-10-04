#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <curses.h>
#include <dirent.h>

#define MAX_INPUT_SIZE 512

/* questions!!
 * 1. what to do with parent processes?
 * 2. syntatically correctness? & and >
 * 3. recommend fgets() not scanf?
 */

// strtok

int execCommand( char * command, char * arg);

int main (int argc, char * argv[]) {
    // since the maximum length of input in shell should be 512B
    char scanfBuffer[MAX_INPUT_SIZE];

    char * command = (char *)malloc(MAX_INPUT_SIZE * sizeof(char));
    char * arg= (char *)malloc(MAX_INPUT_SIZE * sizeof(char));
    int i = 0;

    printf("mysh> ");

    while(1) {

        scanf("%[^\n]%*c", scanfBuffer);

        command = strtok (scanfBuffer, " ");
        arg = strtok (NULL, " ");

        int rc = fork();

        // fork failed
        if(rc < 0) {
            printf("Fork failed\n");
			return 1;
        }
        // in child process, run command
        else if(rc == 0){
            execCommand(command, arg);
        }

        // in parent process
        else {

        }
    }
    return 0;
}

/*
 * Name: execCommand
 * param: string command, string argument.
 * return: error 1, good 0;
 *
 * description: this function takes in the name of a shell command and its
 * (optional) arguments. Now it supports:
 * pwd          - path
 * cd           - return HOME
 * show-dirs    - shows all subdirectories under current directory.
 * show-files   - shows all the files under current directory.
 * mkdir [name] - makes a new folder under current directory.
 * touch [name] - makes a new file under current directory.
 * clear        - it clears the screen.
 * exit         - it exits this shell.
 */
int execCommand( char * command, char * arg) {
    char cwd[1024];
    if(strcmp(command, "pwd") == 0) {
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                fprintf(stdout, "%s\n", cwd);
            }
            else {
                perror("getcwd() error");

                return 1;
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
                else {
                    fprintf(stderr, strcat(arg, " already exists.\n"));

                    return 1;
                }
            }
        }

        else if(strcmp(command, "touch") == 0) {
            FILE* file_ptr = fopen(arg, "w");
            fclose(file_ptr);
        }

        else if(strcmp(command, "clear") == 0) {
            printf("\033[H\033[J");
        }

        else if(strcmp(command, "exit") == 0) {
            exit(1);
        }

        else {
            printf("unrecognized command\n");
        }

        printf("mysh> ");

        return 1;
}
