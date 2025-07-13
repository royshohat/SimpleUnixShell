#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

#include "util.h"
#define INPUT_MAX_SIZE 1024
#define ARGS_MAX_COUNT 20
#define COMMANDS_MAX_COUNT 20

int main(void) {
    char input[INPUT_MAX_SIZE];
    char* commands[COMMANDS_MAX_COUNT];
    char* args[ARGS_MAX_COUNT];
    int commandsCount;
    int argsCount;
    char* newLine;

    while (1) {
        printf("mysh> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL) {
            // Handle Ctrl+d
            printf("\nExiting...\n");
            break;
        }

        // Checks for input length
        if ((newLine = strchr(input, '\n')) == NULL) {
            printf("Error: Input is too long.\n");
            // Clear the rest of the input buffer
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            continue;
        }
        *newLine = '\0'; // Remove the newline character at the end caused by fgets

        if (strlen(input) == 0) { // Handle empty command
            continue;
        }

        parseForPipe(input, commands, &commandsCount);

        // Handle built-ins only if there is a single command (no pipes)
        if (commandsCount == 1) {
            parseToArgs(commands[0], args, &argsCount);

            if (argsCount == 0) {
                continue; // No command entered
            }

            if (strcmp(args[0], "exit") == 0) {
                printf("Exiting...\n");
                return 0; // Exit the shell
            }

            if (strcmp(args[0], "cd") == 0) {
                if (argsCount < 2) {
                    fprintf(stderr, "cd: missing argument\n");
                } else if (chdir(args[1]) != 0) {
                    perror("cd");
                }
                continue;
            }

            if (strcmp(args[0], "pwd") == 0) {
                char cwd[INPUT_MAX_SIZE];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    printf("%s\n", cwd);
                } else {
                    perror("pwd");
                }
                continue;
            }
        }

        int pipefds[(COMMANDS_MAX_COUNT - 1) * 2];
        for (int i = 0; i < commandsCount - 1; i++) {
            if (pipe(pipefds + i * 2) < 0) {
                perror("pipe");
                exit(1);
            }
        }

        for (i = 0; i < commandsCount; i++) {
            pid_t pid = fork();
            if (pid == -1) {
                perror("fork");
                exit(1);
            }

            if (pid == 0) { //inside child process
                if (i > 0) {
                    if (dup2(pipefds[(i - 1) * 2], STDIN_FILENO) < 0) {
                        perror("dup2 input");
                        exit(1);
                    }
                }
                if (i < commandsCount - 1) {
                    if (dup2(pipefds[i * 2 + 1], STDOUT_FILENO) < 0) {
                        perror("dup2 output");
                        exit(1);
                    }
                }

                // Close all pipe file descriptors in the child
                for (int j = 0; j < (commandsCount - 1) * 2; j++) {
                    close(pipefds[j]);
                }

                // Parse and execute the command
                parseToArgs(commands[i], args, &argsCount);
                args[argsCount] = NULL; // execvp needs a NULL-terminated array

                execvp(args[0], args);
                // If execvp returns, an error occurred
                perror(args[0]);
                exit(1);
            }
        }

        // Close all pipe file descriptors in the parent after forking
        for (int j = 0; j < (commandsCount - 1) * 2; j++) {
            close(pipefds[j]);
        }

        // Wait for all child processes to complete
        for (int j = 0; j < commandsCount; j++) {
            wait(NULL);
        }
    }

    return 0;
}
