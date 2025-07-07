#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void){
	pid_t p;
	char buffer[100];
	char* args[20];
	int n;	
	int argumentsFlow;
	int argsCounter = 0;
	char* token;
	char* newLine;	

	while(!0){	
		argumentsFlow = 0;
		argsCounter = 0;

		printf("mysh> ");
		fgets(buffer, 50, stdin);

		if((newLine = strchr(buffer, '\n')) == NULL){
			printf("too long\n");
			continue;	
		}	
		*newLine = '\0';

		token = strtok(buffer, " ");
		
		while(token != NULL){
			if(argsCounter >= 20){
				printf("to much arguments\n");
				argumentsFlow = 1;
				break;
			}		
					
			args[argsCounter] = token;
			argsCounter++;
			token = strtok(NULL, " ");
		}
		args[argsCounter] = NULL;

		if (argumentsFlow) continue;
		

		p = fork();

		if(p==0){
			execvp(args[0], args);
			printf("couldn't load bin\n");
			exit(0);
		}

		usleep(250000);  // 250,000 microseconds = 0.25 seconds
	}
	
	return 0;
}	
