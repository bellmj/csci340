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
int strEquals(const char *s, const char *t)//TODO make this methods an str equals method
{
	while (*s == *t && *s != '\0')
	{
		s++;
		t++;
	}
	if(*s == '\0' && *t == '\0'){
		return 1;
	}
	return 0;
}
int main(int argc, char** argv) {
	char* line = "ls -la";
    command_t* myStruct;
	myStruct =(command_t*) malloc(sizeof(command_t));
    parse(line,myStruct);
	// printf("%s\n",(myStruct->name));
	// printf("%d\n",myStruct->argc); testing parse
	// printf("%s\n",(myStruct->argv[0]));
	// printf("%s\n",(myStruct->argv[1]));

	int done = 0;
	while(!done){
		printf("%s","==>>:" );
  	int maxinputlen = 100;
  	char *input;

  input = (char *) malloc (maxinputlen + 1);
  getline (&input, &maxinputlen, stdin);
	command_t* commandstruct;
	commandstruct = (command_t*)malloc(sizeof(command_t));
	parse(input,commandstruct);
	printf("%s\n",commandstruct->name );
	if(strEquals("exit",commandstruct->name)){
		done = 1;
	}
	//  printf("%d\n",commandstruct->argc);
	//  printf("%s\n",(commandstruct->argv[0]));
	// printf("%s\n",(commandstruct->argv[1]));

	}


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
