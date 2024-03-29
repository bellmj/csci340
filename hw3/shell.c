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
#define MAXSTRLEN 255
#define noop

int my_strncat(char *dest, const char *src, int n);
int my_strncpy(char *dest, const char *src, int n);
int my_strequal(const char *s, const char *t);
int my_strlen(const char* s);
int parseCommandT(command_t *pipedCommandT, command_t *retCmd1,command_t *retCmd2);
int iswhite(char c);

// --------------------------------------------
// Currently only two builtin commands for this
// assignment exist, however in future, more could
// be added to the builtin command array.
// --------------------------------------------
const char* valid_builtin_commands[] = {"cd", "exit", NULL};

// --------------------------------------------
// Implementation for each prototype below
// --------------------------------------------

// get the next token starting from line.  Return length of token.
int get_next_token(char* line, char** token)
{
  int i;                 // for loop control variable
  int start;             // start of some non-white space block
  int inwhite = TRUE;    // TRUE if "in" white space

  // go through the string one character at a time
  for (i = 0; line[i] != '\0'; i++) {  // NOTE:  i incremented ONLY here!
    if (iswhite(line[i])) {  //   did we find a white space?
      if (!inwhite) {        //   if not already in white space
	break;               //       then we got a new token
      }
      inwhite = TRUE;        //   remember the state that we are in white space
    }
    else {                   // not a white space character (ie. an argument)
      if (inwhite) {         // remember where we transitioned from a white
	start = i;           //   to non-white region
      }
      inwhite = FALSE;       // we are now not in a white space state
    }
  }

  if (!inwhite) {            // if we didn't end with a white space
    *token = line + start;   //     then we got a new token
    return i - start;
  }

  *token = NULL;             // if we get here, no tokens available
  return 0;
}

int count_tokens(char* line)
{
  int num_tokens = 0;
  char *token;
  int length = get_next_token(line, &token);

  while (length > 0) {
    num_tokens++;
    line = token + length;
    length = get_next_token(line, &token);
  }

  return num_tokens;
}

void parse(char* line, command_t* p_cmd)
{
  int i;
  int length;
  char *token;

  // get number of command line arguments
  p_cmd->argc = count_tokens(line);

  if (p_cmd->argc > 0) {
    // allocate space for arguments array (+ 1 for NULL)
    p_cmd->argv = (char **) malloc((p_cmd->argc+1) * sizeof(char *));

    for (i = 0; i < p_cmd->argc; i++) {   // for each argument...
      length = get_next_token(line, &token);
      line = token + length;
      p_cmd->argv[i] = (char *) malloc(length + 1);
      my_strncpy(p_cmd->argv[i], token, length);
    }
    p_cmd->argv[i] = NULL;
  }
  else {   // blank line entered
    p_cmd->argv = (char **) malloc(2 * sizeof(char *));
    p_cmd->argv[0] = (char *) malloc(1);
    p_cmd->argv[0][0] = '\0';
    p_cmd->argv[1] = NULL;
  }
  // allocate space and copy argv[0] into name
  p_cmd->name = (char *) malloc(my_strlen(p_cmd->argv[0])+1);
  my_strncpy(p_cmd->name, p_cmd->argv[0], my_strlen(p_cmd->argv[0]));
}

int execute(command_t* p_cmd)
{
  int pid;
  int status;
  char fullpath[MAXSTRLEN];
  char** argArray = p_cmd->argv;
  int pipeCounter;
  for(pipeCounter = 0;pipeCounter <= (p_cmd->argc)-1 && *argArray[pipeCounter] != '|'; pipeCounter = pipeCounter +1){
    noop;
  }//this loop leaves pipeCounter as the index of the pipe or argc if there is no pipe
  if(pipeCounter == p_cmd->argc){
    //Ceci n'est pas une pipe!
    if ((pid = fork()) == 0) {
      find_fullpath(fullpath, p_cmd);
      execv(fullpath, p_cmd->argv);
      perror("Execute terminated with an error condition!\n");
      exit(1);
    }
    return wait(&status);
  } else {
    //this is a pipe
    //TODO call private method to split current command_t struct into 2 command_t structs
    command_t fake1;
    command_t fake2;
    parseCommandT(p_cmd, &fake1, &fake2);
    // printf("%s\n", fake1.name);
    // printf("%d\n",fake1.argc);
    // printf("%s\n", fake2.name);
    // printf("%s\n", fake1.argv[0]);
    // printf("%s\n", fake1.argv[1]);
    // printf("%s\n", fake2.argv[0]);
    // printf("%d\n", fake2.argc);
    // printf("%s\n", fake2.argv[1]);
    // printf("%s\n", fake2.argv[2]);

    int child_process_status;
    int fds[2];
    pid_t cpid1, cpid2;
    pipe(fds);
    if ((cpid1 = fork()) == 0) {
      close(1); /* close normal stdout */
      dup(fds[1]); /* make stdout same as fds[1] */
      close(fds[0]); /* we don’t need this */
      char * fullPath1 = (char *)malloc(MAXSTRLEN);
      find_fullpath(fullPath1,&fake1);
      execv(fullPath1, fake1.argv);
      exit(1);
    }
    if ((cpid2 = fork()) == 0) {
      close(0); /* close normal stdin */
      dup(fds[0]); /* make stdin same as fds[0] */
      close(fds[1]); /* we don’t need this */
      char * fullPath2 = (char *)malloc(MAXSTRLEN);
      find_fullpath(fullPath2,&fake2);
      execv(fullPath2, fake2.argv);
      exit(1);
    }
    close(fds[0]);
    close(fds[1]);
    waitpid(cpid1, &child_process_status, 0);
    waitpid(cpid2, &child_process_status, 0);


    return -1;

  }



  //the old execute code before pipes were allowed
  // if ((pid = fork()) == 0) {
  //   find_fullpath(fullpath, p_cmd);
  //   execv(fullpath, p_cmd->argv);
  //   perror("Execute terminated with an error condition!\n");
  //   exit(1);
  // }


}

int find_fullpath(char* fullpath, command_t* p_cmd)
{
  int i;
  int start = 0;
  char dir[MAXSTRLEN];    // directory stripped from PATH
  char *mypathvar;        // copy of string returned by getenv("PATH")
  struct stat sb;         // for stat() call
  char *pathvar = getenv("PATH");
  int pathvarlen = my_strlen(pathvar);

  // allocate space for pathvar (+ appending a colon and null character)
  // copy pathvar into mypathvar with extra colon appended
  // this allows all processing to occur within the loop
  mypathvar = (char *) malloc(pathvarlen+2);
  my_strncpy(mypathvar, pathvar, pathvarlen);
  mypathvar[pathvarlen] = ':';  mypathvar[pathvarlen+1] = '\0';

  for (i = 0; mypathvar[i] != '\0'; i++) {
    if (mypathvar[i] == ':') {
      my_strncpy(dir, mypathvar+start, i - start);
      start = i+1;
      // build the fullpath string
      my_strncpy(fullpath, dir, MAXSTRLEN);
      my_strncat(fullpath, "/", MAXSTRLEN);
      my_strncat(fullpath, p_cmd->name, MAXSTRLEN);

      if (stat(fullpath, &sb) != -1 && S_ISREG(sb.st_mode)) {
	  return TRUE;
      }
    }
  }

  return FALSE;
}

int is_builtin(command_t* p_cmd)
{
  int i;

  for (i = 0; valid_builtin_commands[i] != NULL; i++) {
    if (my_strequal(p_cmd->name, valid_builtin_commands[i]))
      return TRUE;
  }
  return FALSE;
}

int do_builtin(command_t* p_cmd)
{
  if (my_strequal(p_cmd->name, valid_builtin_commands[0]))
    return chdir(p_cmd->argv[1]);

  // can add more commands ...

  return SUCCESSFUL;
}

void cleanup(command_t* p_cmd)
{
  int i;

  free(p_cmd->name);
  p_cmd->name = NULL;
  for (i = 0; i < p_cmd->argc; i++) {
    free(p_cmd->argv[i]);
    p_cmd->argv[i] = NULL;
  }
  free(p_cmd->argv);
  p_cmd->argv = NULL;
  p_cmd->argc = 0;
}
//My utility FUNCTIONS
/**
*This method takes 3 command_t structs as input. The first struct should be populated and the second and third struct are for return
* @param pipedCommandT: a command_t struct that contains the original command and inside of argv it contains pipe charcter followed by the parsed command
* @return retCmd1 a command_t struct that is the first command;
* @return retCmd2 a command_t struct that is the second command after the pipe
*/
int parseCommandT(command_t *pipedCommandT, command_t *retCmd1,command_t *retCmd2){
  int pipeCounter;
    for(pipeCounter = 0;pipeCounter <= (pipedCommandT->argc)-1 && *((pipedCommandT->argv)[pipeCounter]) != '|'; pipeCounter = pipeCounter +1){
      noop;
    }
    if(pipeCounter == pipedCommandT->argc)
       perror("there is no pipe to parse");
    char * cmdOne = (char *)malloc(MAXSTRLEN);
    for(int i = 0; i < pipeCounter;i++){
      my_strncat(cmdOne,pipedCommandT->argv[i],MAXSTRLEN);
      my_strncat(cmdOne," ",MAXSTRLEN);
    }
    parse(cmdOne,retCmd1);
    char * cmdTwo = (char *)malloc(MAXSTRLEN);
    for(int i = pipeCounter+1;i<= pipeCounter + (pipedCommandT->argc - pipeCounter-1);i++){
      my_strncat(cmdTwo,pipedCommandT->argv[i],MAXSTRLEN);
      my_strncat(cmdTwo," ",MAXSTRLEN);
    }
    parse(cmdTwo,retCmd2);

//   retCmd1->name = (char*)malloc(sizeof(pipedCommandT->name));
//   my_strncpy(retCmd1->name,pipedCommandT->name,my_strlen(pipedCommandT->name));
//   int pipeCounter;
//   for(pipeCounter = 0;pipeCounter <= (pipedCommandT->argc)-1 && *((pipedCommandT->argv)[pipeCounter]) != '|'; pipeCounter = pipeCounter +1){
//     noop;
//   }
//   if(pipeCounter == pipedCommandT->argc)
//     perror("there is no pipe to parse");
//   int justTemp = pipedCommandT->argc;
//   retCmd2->argc = justTemp - pipeCounter-1;
//   printf("The argc for retCmd2 is:%d\n",retCmd2->argc );
//   retCmd1->argc = pipeCounter;
//   retCmd2->name = (char*)malloc(sizeof((pipedCommandT->argv)[pipeCounter+1]));
//   my_strncpy(retCmd2->name,(pipedCommandT->argv)[pipeCounter+1], my_strlen((pipedCommandT->argv)[pipeCounter+1]));
//   retCmd1->argv = (char**)malloc((retCmd1->argc+1) * sizeof(char *));
//   retCmd2->argv = (char**)malloc((retCmd2->argc+1) * sizeof(char *));
//   int i;
// //  printf("%s\n",pipedCommandT->argv[0] );
//   for(i = 0; i < retCmd1->argc;i++){
//   //  printf("\t\t%d\n",i );
//     retCmd1->argv[i] = (char *)malloc(my_strlen((pipedCommandT->argv)[i])+1);
//
//     my_strncpy((retCmd1->argv)[i],(pipedCommandT->argv)[i],my_strlen((pipedCommandT->argv)[i]));
//   }
//   retCmd1->argv[i] = NULL;
//   for( i = pipeCounter+1; i <= pipeCounter + retCmd2->argc;i++){//TODO start working here
//     printf("%d\n",i );
//     retCmd2->argv[i] = (char *)malloc(my_strlen((pipedCommandT->argv)[i])+1);
//     my_strncpy((retCmd2->argv)[i],(pipedCommandT->argv)[i],my_strlen((pipedCommandT->argv)[i]));
//      printf("%s\n",(retCmd2->argv)[i] );
//   }
//   retCmd2->argv[i] = NULL;



  return 1;

}




// **** Leclerc's UTILITY FUNCTIONS

int my_strlen(const char* s)
{
  int count = 0;
  while (*s++ != '\0')
    count++;

  return count;
}

// assumes properly terminated strings
int my_strequal(const char *s, const char *t)
{
  while (*s != '\0' && *s == *t) {
    s++; t++;
  }

  return *s == '\0' && *t == '\0';
}

int my_strncpy(char *dest, const char *src, int n)   // copy dest to src
{
  while (*src != '\0' && n--) {
    *dest++ = *src++;
  }
  *dest = '\0';

  return 0;
}

int my_strncat(char *dest, const char *src, int n)   // append dest to src
{
  while (--n > 0 && *dest != '\0')
    dest++;    // move to the end of dest

  while (*src != '\0' && n > 0) {
    *dest++ = *src++;
    n--;
  }
  *dest = '\0';

  return 0;
}

int iswhite(char c)
{
  return c == ' ' || c == '\t';
}
