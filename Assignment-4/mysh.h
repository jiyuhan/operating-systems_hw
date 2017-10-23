

/*========= utility function ============*/
/* this safely gets user's command line input for args */
void get_input(char * argStr);

/* this tokenizes all the user inputs into a string array and strips all the ows (optional white space) */
void tokenize(char * arg, char * token[], int * argcount);

/* this checks if the command is a built-in command */
int isBuiltInCommand(char * command);

/* this checks the args for redirection and detachment, assuming syntactically correct */
/*WARNING: carefully use this command because it strips all redirection or detachment statement*/
void setFlagReg(char * flag, char * args[], int argcount, char * redir_path);

/* this runs all the built-in commands from hw3 */
void exec_v(char * args[]);

/*========= command functions ===========*/

/* pwd */
void pwd();

/* cd and cd [dir] */
void cd(char * args[]);

/* show-dirs */
void showdir();

/* show-files */
void showfiles();

/* mkdir [dir] */
void mkdir_c(char * args[]);

/* touch [file] */
void touch(char * args[]);

/* clear */
void clear_c();

void wait_c();

int shiftIfPy(char * args[], int argcount);
