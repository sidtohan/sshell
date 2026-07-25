#include "tokenizer.h"
void tokenize(char *buf) {
    int argc;
    char* argv[64];
    char* token = strtok(buf, " \t\r\n\v\f");
    char* command = NULL;
    int8_t redirect = 0;
    char* redirect_fname = NULL;

    if (!token) // Empty
        return;
    
    command = token;
    while (token != NULL) {
        // Special case: token is '>' or '>>'. In this case, we have redirection on our hands.
        if (strncmp(token, ">", 2) == 0) {
            redirect |= 1;
            token = strtok(NULL, " \t\r\n\v\f");
            redirect_fname = token;
            break;
        } else if (strncmp(token, ">>", 2) == 0) {
            redirect |= 2;
            token = strtok(NULL, " \t\r\n\v\f");
            redirect_fname = token;
            break;
        }
        argv[argc++] = token;
        token = strtok(NULL, " \t\r\n\v\f");
    }

    if (redirect) {
        // Currently, any token after the first token that follows '>'
        // or '>>' is discarded..
        while (token != NULL)
            token = strtok(NULL, " \t\r\n\v\f");
    }

    argv[argc] = 0;
    executeCommand(command, argc, argv, redirect, redirect_fname);
}
