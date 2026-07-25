#include "tokenizer.h"
#include <string.h>

void tokenize(char *buf) {
    int argc;
    char* argv[64];
    char* token = strtok(buf, " \t\r\n\v\f");
    char* command = NULL;
    int8_t redirect = 0;
    int8_t temp1, temp2;
    char* redirect_fname = NULL;

    if (!token) // Empty
        return;
    
    command = token;
    while (token != NULL) {
        // Special case: token is '>' or '>>'. In this case, we have redirection on our hands.
        // Keep parsing
        if ((temp1 = strncmp(token, ">>", 2) == 0) || (temp2 = strncmp(token, ">", 2) == 0)) {
            if (redirect) {
                printf("sshell: Multiple redirects detected.\n"); 
                // Exhaust all tokens.
                while (token != NULL) 
                    token = strtok(NULL, " \t\r\n\v\f");
                return;
            }
            // 0th bit: for trunc
            // 1st bit: for append
            redirect |= (temp1 ? APP_BIT : TRUNC_BIT);
            token = strtok(NULL, " \t\r\n\v\f");
            redirect_fname = token;
            // Do it twice. Because we don't want the filename as one of the args.
            token = strtok(NULL, " \t\r\n\v\f");
            continue;
        }
        argv[argc++] = token;
        token = strtok(NULL, " \t\r\n\v\f");
    }

    argv[argc] = 0;
    executeCommand(command, argc, argv, redirect, redirect_fname);
}
