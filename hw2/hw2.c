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
//
int main(int argc, char** argv) {
	char* line = "ls -f /helloWorld";
	struct command_t *myStruct;
	myStruct = malloc(sizeof(command_t));
	myStruct->name = "hello";
	printf("%s\n%s\n",line,*myStruct->name );

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

	return 0;

} // end main function
