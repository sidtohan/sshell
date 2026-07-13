#include <assert.h>
#include <linux/limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#include "custom.h"


// TODOS;
// 1. Core Shell
// 2. Built Ins like CD etc.
// 3. File Descriptors (<, >, >>)
// 4. IPC (Pipes)
// 5. Process Management.
// 6. Extras (Quoted Strings, Environment Variables, History)

// GLOBALS
char cwd[PATH_MAX];

void executeCommand(char *token) {
    // For most commands, will prefer external implementation for now.
    // For cd, will use chdir.
    char *argv[64];
    int argc = 0;
    int pid = 0;
    int redirect = 0;
    char *command;
    
    if (!token)
        return;
    
    command = token;
    while (token != NULL) {
        // Edge case: token is '>'. In this case, we have redirection on our hands.
        if (*token == '>') {
            redirect = 1;
            token = strtok(NULL, " \t\r\n\v\f");
            break;
        }
        argv[argc++] = token;
        token = strtok(NULL, " \t\r\n\v\f");
    }
    argv[argc] = 0;
    

    // Use custom implementation for some commands.
    switch (handleCustom(argc, argv)){
    case CUSTOM_FAIL:
        // Error: need to return something to user..
        return;
    case CUSTOM_SUCCESS:
        return;
    case CUSTOM_NOMATCH:
        break;
    default:
        // Shouldn't be here. Only Three Codes allowed.
        assert(0);
    };

    pid = fork();
    
    if (pid == -1) {
        printf("Fork failed. Exiting");
        return;
    }

    if (pid == 0) {
        // Now need to handle redirect scenario.
        // TODO: extend for custom commands also.. Might require args change.
        if (redirect) {
            int fd;
            char *filename = token;
            // Get file name
            // Only consider the first param.. Rest can be ignored..
            while (token != NULL) {
                token = strtok(NULL, " \t\r\n\v\f");
            }
    
            // For '>'. This is fine. TODO: add more like >>
            fd = open(filename, O_WRONLY | O_CREAT, S_IWUSR | S_IRUSR);
            if (fd == -1) {
                printf("sshell: Error opening file for redirect\n");
                exit(EXIT_FAILURE);
            }
    
            // Overwrite STDOUT_FILENO with opened file..
            dup2(fd, STDOUT_FILENO);
            if(close(fd) == -1) {
                printf("sshell: Error closing file internally for redirect\n");
                exit(EXIT_FAILURE);
            }
        }
        // Child
        execvp(command, argv);
    } else {
        waitpid(pid, NULL, 0);
        // Second param is for storing exit status. NULL means don't store.
        // Last param is options. 0 is default blocking behaviour.
    } 
}

void inputLoop() {
    char *buf = NULL;
    char *token = NULL;
    size_t buf_size = 0;
    ssize_t char_count = 0; 
    while (1) {
        getcwd(cwd, sizeof(cwd));
        printf("%s $ ", cwd);
        if ((char_count = getline(&buf, &buf_size, stdin)) == -1) {
            printf("Error encountered when reading. Aborting\n");
            free(buf);
            return;
        }
        
        // Tokenize.
        token = strtok(buf, " \t\r\n\v\f");
        executeCommand(token);
    }

}

// Simple Shell Implementation.
int main() {
    inputLoop(); 
}
