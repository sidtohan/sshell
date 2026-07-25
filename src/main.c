#include <assert.h>
#include <linux/limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#include "tokenizer.h"

// TODOS;
// 1. Core Shell
// 2. Built Ins like CD etc.
// 3. File Descriptors (<, >, >>)
// 4. IPC (Pipes)
// 5. Process Management.
// 6. Extras (Quoted Strings, Environment Variables, History)

// GLOBALS
char cwd[PATH_MAX];

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
        
        tokenize(buf);
    }

}

// Simple Shell Implementation.
int main() {
    inputLoop(); 
}
