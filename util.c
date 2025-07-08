#include <stdio.h>
#include <string.h>

#include "util.h"

int parseToArgs(char* buffer, char** args, int* argsCounter){

	char* token;
  token = strtok(buffer, " ");

  while(token != NULL){
    if(*argsCounter >= 20){
      printf("to much arguments\n");
      return 1;
    }		
        
    args[*argsCounter] = token;
    (*argsCounter)++;
    token = strtok(NULL, " ");
  } 

  return 0;
}
