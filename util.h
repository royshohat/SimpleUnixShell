#define MAX_ARGS 20
#define MAX_COMD 20

void parseToArgs(char* buffer, char** args, int* argsCount);
void parseForPipe(char* buffer, char** args, int* commendsCount);
