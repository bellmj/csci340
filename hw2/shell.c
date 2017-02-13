// ----------------------------------------------
// These are the only libraries that can be 
// used. Under no circumstances can additional 
// libraries be included
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "shell.h"

// --------------------------------------------
// Currently only two builtin commands for this
// assignment exist, however in future, more could 
// be added to the builtin command array.
// --------------------------------------------
const char* valid_builtin_commands[] = {"cd", "exit", NULL};

// --------------------------------------------
// Implementation for each prototype below
// --------------------------------------------
// void parse(char* line, command_t* p_cmd);
// int execute(command_t* p_cmd);
// int find_fullpath(char* fullpath, command_t* p_cmd);
// int is_builtin(command_t* p_cmd);
// int do_builtin(command_t* p_cmd);
// void cleanup(command_t* p_cmd);
