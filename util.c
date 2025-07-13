#include <stdio.h>
#include <string.h>

#include "util.h"

void parseToArgs(char* commend, char** args, int* argsCounter){
	*argsCounter = 0;

	char* token;
  token = strtok(commend, " ");

  args[*argsCounter] = token;
  (*argsCounter)++;
  token = strtok(NULL, " ");
}
// returns amount of commends
void parseForPipe(char* buffer, char** commends, int* commendsCount){
  *commendsCount = 0;
	char* token;
  token = strtok(buffer, "|");

  while(token != NULL){
    commends[*commendsCount] = token;
    token = strtok(NULL, "|");
    (*commendsCount)++;
  } 
}
