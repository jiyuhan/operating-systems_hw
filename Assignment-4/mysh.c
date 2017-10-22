#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <curses.h>
#include <dirent.h>

#define MAX_INPUT_SIZE 513

/* questions!!
 * 1. what to do with parent processes?
 * 2. syntatically correctness? & and >
 > pg. 44, figure 4-5 in the book it has the code for redirection
 * 3. recommend fgets() not scanf?

 * 1. scanf("%[^\n]%*c", scanfBuffer); // how to ensure that
 * 2. detach process
 */

// strtok


/*
    BONUS POINT:
        USERNAME:
    Read from an input file: ???

    GIVEN A PYTHON:


    // prototype functions
    void getInput();
    int isBuiltInCommand(char);
    int execBuiltInCommand();

    main() {
        while(1) {
            get_input(); // somehow

            if(strcmp(Token[0], "exit") == 0) return 0;

            // then it runs the process using execv()
            if(isBuiltInCommand(Token[0]) == 1) execv(Tokens[0], Tokens);
            // this means that it is not a built in command
            else {
                int rc = fork();

                if(rc < 0) {
                    printf("Fork failed\n");
                    return 1;
                }
                // child process
                else if( rc == 0) {
                    close(STDOUT_FILENO);
                    if(redirection) execv(Tokens[0], Tokens);
                }
                // parent process
                else {
                    if(! check&) wait(pid); //
                }

            }
        }
    }

    waitpid(PID)
    or
    wait(NULL)
    use a linked list to get PID
 */


int execCommand(char * args[]);

int main (int argc, char * argv[]) {
    // since the maximum length of input in shell should be 512B
    char scanfBuffer[MAX_INPUT_SIZE];

    char * args[MAX_INPUT_SIZE];
    int i = 0;

    printf("mysh> ");

    while(1) {
        //TODO: how to make it continuously read inputs
        for(int bufferCount = 0; bufferCount < MAX_INPUT_SIZE; bufferCount++) {
            scanf("%c", scanfBuffer[bufferCount]);
            if(scanfBuffer[bufferCount - 1] != "\n") scanf("%c", scanfBuffer[bufferCount]);
        }
        // for(int bufferCount = 0; bufferCount < MAX_INPUT_SIZE; bufferCount++) {
        //     scanf("%c", scanfBuffer[bufferCount]);
        // }

        args[0] = strtok(scanfBuffer, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }


        int rc = fork();

        // fork failed
        if(rc < 0) {
            printf("Fork failed\n");
			return 1;
        }
        // in child process, run command
        else if(rc == 0){
            execvp(args[0], args);
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
int execCommand(char * args[]) {
    char cwd[1024];
    if(strcmp(args[0], "pwd") == 0) {
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            fprintf(stdout, "%s\n", cwd);
        }
        else {
            perror("getcwd() error");

            return 1;
        }
    }

    else if(strcmp(args[0], "cd") == 0) {
        if(args[1] == NULL) {
            chdir(getenv("HOME"));
        } else {
            chdir(args[1]);
        }
    }

    else if(strcmp(args[0], "show-dirs") == 0) {
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

    else if(strcmp(args[0], "show-files") == 0) {
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

    else if(strcmp(args[0], "mkdir") == 0) {
        if(args[1] == NULL) printf("mkdir [new folder name]\n");
        else {
            char message[1024];
            strcat(message, args[1]);
            strcat(message, " already exists.\n");
            if(! mkdir(args[1], 0755)) {}
            else {
                fprintf(stderr, strcat(args[1], " already exists.\n"));
                return 1;
            }
        }
    }

    else if(strcmp(args[0], "touch") == 0) {
        FILE* file_ptr = fopen(args[1], "w");
        fclose(file_ptr);
    }

    else if(strcmp(args[0], "clear") == 0) {
        printf("\033[H\033[J");
    }

    else if(strcmp(args[0], "exit") == 0) {
        exit(1);
    }

    else {
        printf("unrecognized command\n");
    }

    printf("mysh> ");

    return 1;
}
