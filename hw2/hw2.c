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

// -----------------------------------
// Main function
// Arguments:	argc = number of arguments suppled by user
//				argv = array of argument values
//

int main(int argc, char** argv) {
	char* line = "ls -la";
    command_t* myStruct;
	myStruct =(command_t*) malloc(sizeof(command_t));
    parse(line,myStruct);
	printf("%s\n",(myStruct->name));
	printf("%d\n",myStruct->argc);
	printf("%s\n",(myStruct->argv[0]));
	printf("%s\n",(myStruct->argv[1]));


	// ----------------------------------
	// Pseudocode
	// ----------------------------------
	// while (!done)
	//		print the prompt (i.e. >, #, or $ ... your choice)
	//		read command line
	//		parse the command line
        //      if (parsed command is "exit")
        //      	done = true
	//  	else if (is _builtin(...))
	//			do_builtin(...)
	//		else if (find_fullpath(...))
	//  		execute(...)
	//		else
	//			error()
	// 		cleanup(...)
	//
	free(myStruct);

	return 0;

} // end main function
