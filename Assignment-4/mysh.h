

/*========= utility function ============*/
void get_input(char * argStr);
void tokenize(char * arg, char * token[], int * argcount);
int isBuiltInCommand(char * command);
void setFlagReg(char * flag, char * args[], int argcount);


/*========= command functions ===========*/
void exec_v(char * args[]);
void pwd();
void cd(char * args[]);
void showdir();
void showfiles();
void mkdir_c(char * args[]);
void touch(char * args[]);
void clear_c();
