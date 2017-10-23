#include "include.h"

int main(int argc, char * argv[]) {
    // since the maximum length of input in shell should be 512B
    char scanfBuffer[MAX_INPUT_SIZE];
    char * token[MAX_INPUT_SIZE];
    char redir_path[MAX_INPUT_SIZE];

    int i = 0;
    int argcount = 0;

    /*
     * this register uses bit manipulation to manages # of flags
     *      get:    Flag_Reg & (1 << NORMAL_JOB_FLAG)
     * 0 if the command is NORMAL_JOB_FLAG
     * 1 if the command is BACKGROUND_JOB_FLAG
     * 2 if the command is REDIRECTION_JOB_FLAG
     * 3 if the command is ERROR_JOB_FLAG
     * TODO: 4 ~ 7 reserved
     */
    char Flag_Reg = 0;

    int rc = 0;
#if 1
    while(1) {
        printf("mysh> ");
        get_input(scanfBuffer);
        tokenize(scanfBuffer, token, &argcount);

        if(strcmp(token[0], "exit") == 0) return 0;

        //TODO: if the following assumption is correct?
        // if it's built in command, we should ignore the "&" and ">" after.
        if(isBuiltInCommand(token[0]) == 0) {
            printf("it is a built-in command\n");
            exec_v(token);
        }
        else {
            setFlagReg(&Flag_Reg, token, argcount, redir_path);
            if((Flag_Reg & (1 << ERROR_JOB_FLAG)) != 0) {
                char error_message[30] = "An error has occured\n";
                write(STDERR_FILENO, error_message , strlen(error_message));
                break;
            }

            if((rc = fork()) < 0) {
                char error_message[30] = "An error has occured\n";
                write(STDERR_FILENO, error_message , strlen(error_message));
                return 1;
            }
            // child process
            else if( rc == 0) {
                printf("child: %d\n", (int) getpid());
                if((Flag_Reg & (1 << REDIRECTION_JOB_FLAG)) != 0) {
                    close(STDOUT_FILENO);
                    open(redir_path, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

                    execvp(token[0], token);
                }

                else {
                    execvp(token[0], token);
                }
            }
            // parent process
            else {
                // if(! check&) wait(pid); //
                if((Flag_Reg & (1 << BACKGROUND_JOB_FLAG)) != 0) {
                    printf("pushing: \n");
                    // push rc to queue
                    //
                } else {
                    printf("waiting\n");
                    wait(NULL);
                }
                // printf("child process: [%d]\n", rc);
                // // wait(NULL) ;
            }
        }
    }
#else
    printf("DEBUG MODE\n");
    printf("before initialzed redir_path: %s\n", redir_path);
    while(1) {
        printf("mysh > ");
        get_input(scanfBuffer);
        tokenize(scanfBuffer, token, &argcount);
        setFlagReg(&Flag_Reg, token, argcount, redir_path);
        if((Flag_Reg & (1 << REDIRECTION_JOB_FLAG)) != 0) {
            printf("now redir_path: %s\n", redir_path);
            // close(STDERR_FILENO);
            // open();

            if(execvp(token[0], token) < 0) {
                char error_message[30] = "An error has occured\n";
                write(STDERR_FILENO, error_message , strlen(error_message));
            }
        }
    }
#endif
    free(token);
    return 0;
}


void get_input(char * argStr) {
    int bufferCount = 0;

    // read the first char at 0
    scanf("%c", &argStr[bufferCount]);

    while(bufferCount < MAX_INPUT_SIZE) {
        // if the previous entry was /n, then break out of the loop.
        // if it was not, then read another character after it.
        if(argStr[bufferCount] !=  '\n') {
            bufferCount++;
            scanf("%c", &argStr[bufferCount]);
        }
        else {
            argStr[bufferCount] = '\0';
            break;
        }
    }
}

void tokenize(char * arg, char * token[], int * argcount) {
    int i = 0;
    token[0] = strtok(arg, " ");
    while (token[i] != NULL) {
        i++;
        token[i] = strtok(NULL, " ");
    }

    *argcount = i;
}

int isBuiltInCommand(char * command) {
    char * builtInCommandList[8] = {"pwd", "cd", "show-dirs", "show-files", "mkdir", "touch", "clear", "exit"};

    for(int i = 0; i < 8; i++)
        if(strcmp(command, builtInCommandList[i]) == 0) return 0;
    return 1;
}

void setFlagReg(char * flag, char * args[], int argcount, char * redir_path) {
    // clear all flags before start
    *flag = 0;
    int i = 0;

    if(argcount == 1) {
        *flag |= (1 << NORMAL_JOB_FLAG);
        return;
    }

    /* if had & */
    if(strcmp(args[argcount - 1], "&") == 0) {

        if(argcount == 2) {
            *flag |= (1 << BACKGROUND_JOB_FLAG);
            args[argcount - 1] = NULL;
            return;
        }
        /* check if one has > in front of & */
        if(strcmp(args[argcount - 3], ">") == 0) {
            *flag |= (1 << REDIRECTION_JOB_FLAG);
            strcpy(redir_path, args[argcount - 2]);
            for(i = 1; i <= 3; i++) {
                args[argcount - i] = NULL;
            }
        }
        /* if there is no argument for >, then it's bad command input */
        else if(strcmp(args[argcount - 2], ">") == 0) {
            *flag |= (1 << ERROR_JOB_FLAG);
        }
        return;
    }

    /* if doesn't have & then check for > with valid input after it */
    if(strcmp(args[argcount - 2], ">") == 0) {
        *flag |= (1 << REDIRECTION_JOB_FLAG);
        strcpy(redir_path, args[argcount - 1]);
        for(i = 1; i <= 2; i++) {
            args[argcount - i] = NULL;
        }
    }

    /* if doesn't have an arg after >, then it's bad command input */
    else if(strcmp(args[argcount - 1], ">") == 0) {
        *flag |= (1 << ERROR_JOB_FLAG);
    }

    /* nothing special, then it's normal command */
    else {
        *flag |= (1 << NORMAL_JOB_FLAG);
    }
}

void exec_v(char * args[]) {
    char * command = args[0];
    if(strcmp(command, "pwd") == 0) pwd();
    else if(strcmp(command, "cd") == 0) cd(args);
    else if(strcmp(command, "show-dirs") == 0) showdir();
    else if(strcmp(command, "show-files") == 0) showfiles();
    else if(strcmp(command, "mkdir") == 0) mkdir_c(args);
    else if(strcmp(command, "touch") == 0) touch(args);
    else if(strcmp(command, "clear") == 0) clear_c();
    else if(strcmp(command, "exit") == 0) exit(0);
}

void pwd() {
    char cwd[MAX_INPUT_SIZE];
    if (getcwd(cwd, sizeof(cwd)) != NULL) fprintf(stdout, "%s\n", cwd);
    else perror("getcwd() error");
}

void cd(char * args[]) {
    if(args[1] == NULL) {
        chdir(getenv("HOME"));
    } else {
        chdir(args[1]);
        //TODO: validate path
    }
}

void showdir() {
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

void showfiles() {
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

void mkdir_c(char * args[]) {
    if(args[1] == NULL) printf("mkdir [new folder name]\n");
    else {
        char message[1024];
        strcat(message, args[1]);
        strcat(message, " already exists.\n");
        if(! mkdir(args[1], 0755)) {}
        else {
            // fprintf(stderr, strcat(args[1], " already exists.\n"));
            char error_message [30] = "file already exists\n";
            write(STDERR_FILENO, error_message , strlen(error_message));
        }
    }
}

void touch(char * args[]) {
    FILE* file_ptr = fopen(args[1], "w");
    fclose(file_ptr);
}

void clear_c() {
    printf("\033[H\033[J");
}
