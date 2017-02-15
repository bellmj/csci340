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
/* ----------------------------------------------------------------------------

This function will parse the command (cmd for short) and its arguments
specified by the user.

HINT(s): This function is "essentially" an exercise in string parsing.

        EXAMPLE#1, if the user enters

				cd /mnt/cdrom

		at the shell prompt, line would contain "cd /mnt/cdrom".
		Using the space character as the delimiter, the fields in
		the command struct would be:

				- name = "cd"
				- argc = 2
				- argv = {"cd", "/mnt/cdrom", NULL}

        EXAMPLE#2, if the user enters

				ls -la

		at the shell prompt, line would contain "ls -la". Using the
		space character as the delimiter, the fields in the command
		struct would be:

				- name = "ls"
				- argc = 2
				- argv = {"ls", "-la", NULL}

        EXAMPLE#3, if the user enters nothing at the shell prompt (i.e.
        simply hits the return key), line would NULL, and the fields in
        the command struct would be:

				- name = NULL
				- argc = 0
				- argv = {NULL}

 function:
	- parameter(s): char* pointer that contains the cmd and its arguments,
			and a pointer to an existing command_t structure
	- return: N/A

*/
void parse(char* line, command_t* p_cmd){
  int numOfChars = 0;
  int numOfSpacesToRemove = 0; //the number of trailing spaces in the char* line
  for(int i = 0;line[i]!='\0';i=i+1){//loops through the char* line and counts the number of chars in the char* line
    numOfChars = i + 1;
  }
  while(*(line+numOfChars -1) == ' '){
      numOfSpacesToRemove = numOfSpacesToRemove + 1;
      numOfChars = numOfChars - 1;//sets numOfChars to the correct number of chars minus the spaces at the end
  }
  char * lineMinusSpaces = (char*)malloc(numOfChars);
  printf("the size of the new string is %d\n",numOfChars);
  for(int i = 0; i < numOfChars;i=i+1){//assigns line to lineMinusSpaces without the trailing spaces
    *(lineMinusSpaces + i) = line[i];
  }
  lineMinusSpaces[numOfChars]= '\0';//terminates the string without spaces
  //todo here I have a line with no trailling spaces
  //I can count the number of spaces to get the number of arguments here\/
  int numOfSpaces = 0;

  for(int i = 0;lineMinusSpaces[i]!='\0';i=i+1){//loops through char* line and counts the number of spaces in the char* line
    if(lineMinusSpaces[i]==' '){
      numOfSpaces = numOfSpaces + 1;
    }
  }
  int locationOfSpaces[numOfSpaces+2];
  locationOfSpaces[0] = -1;//assigns zero as the first space so we can take a substring from first_location +1 to next_location -1 (inclusive)
  locationOfSpaces[numOfSpaces+1] = numOfChars;
  int spaceCounter = 1;
  for(int i = 0;lineMinusSpaces[i]!='\0';i=i+1){//loops through char* line again but this time it remembers where each space was located.
    if(lineMinusSpaces[i]==' '){
      locationOfSpaces[spaceCounter] = i;
      spaceCounter = spaceCounter + 1;
    }
  }
   //this loops prints the locations of valid spaces within line including a -1 first element, and a last element (sizeof line) as an implict space
  for(int i = 0; i < numOfSpaces+2;i= i + 1){
    printf("\t\t%d\n",locationOfSpaces[i] );
  }
  //
  //  AT THIS POINT ARGC IS THE ONLY THING CALCULATED
  char ** argvTemp;//numOfSpaces + 1 is the same as argc
  argvTemp = (char**) malloc(sizeof(numOfSpaces+1));
for(int i = 0;i<=numOfSpaces;i=i+1){//this loop is trying to assign the line elements to their position in argv
    int sizeOfArgument = (locationOfSpaces[i+1]-locationOfSpaces[i])- 1;
    printf("%d\n",sizeOfArgument );
    argvTemp[i] = (char*) malloc(sizeof(sizeOfArgument));
}
  // printf("%s\n",lineMinusSpaces);//for some reason printing this line here allows line to be passed to main
  // p_cmd->argv = argv;
  p_cmd->argc = numOfSpaces+1;//assigns argc to be the number of spaces in the line plus one
  p_cmd->name = lineMinusSpaces;

}
// int is_builtin(command_t* p_cmd);
// int do_builtin(command_t* p_cmd);
// int find_fullpath(char* fullpath, command_t* p_cmd);
// int execute(command_t* p_cmd);
// void cleanup(command_t* p_cmd);
