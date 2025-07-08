#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "util.h"

int main(void){
	pid_t p;
	char buffer[100];
	char* args[20];
	int n;	
	int argsCounter = 0;
	char* newLine;	

	while(!0){	
		argsCounter = 0;

		printf("mysh> ");
		fgets(buffer, 50, stdin);

		if((newLine = strchr(buffer, '\n')) == NULL){
			printf("too long\n");
			continue;	
		}	
		*newLine = '\0'; //the last argument has /n from fgets

    //returns one if args went above 20 
    
		if (parseToArgs(buffer, args, &argsCounter)==1) continue;

		args[argsCounter] = NULL;
    
    for(int i=0; i<argsCounter; i++){
      if(strcmp(args[i], "|")){
        //will be handled later             
      }
      if(strcmp(args[i], ">")){
        //will be handled later             
      }
      if(strcmp(args[i], "<")){
        //will be handled later             
      }
    }
    
      
		if(strcmp(args[0], "exit") == 0 && argsCounter == 1){
			printf("exiting...\n");
			exit(0);
		}
		else if(strcmp(args[0], "pwd") == 0 && argsCounter == 1){
			getcwd(buffer, 100); // reusing the buffer cause i can 
			printf("%s\n", buffer);
			continue;
		}
		else if(strcmp(args[0], "cd") == 0 && argsCounter == 2){
			chdir(args[1]);
			continue;
		}
		p = fork();

		if(p==0){
			execvp(args[0], args);
      // returns only if error occurred 
			printf("couldn't load bin\n");
			exit(0);
		}
    wait(NULL);

		usleep(250000);  // 250,000 microseconds = 0.25 seconds
	}
	
	return 0;
}	

