#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// TODOS;
// 1. simple input loop. (DONE)
// 2. call actual func via fork api.
// 3. redirection support.
// 4. pipe etc.
// 5. catching signals.
void inputLoop() {
    char *buf = NULL;
    char *token = NULL;
    size_t buf_size = 0;
    ssize_t char_count = 0; 
    while (1) {
        printf(">> ");
        if ((char_count = getline(&buf, &buf_size, stdin)) == -1) {
            printf("Error encountered when reading. Aborting\n");
            free(buf);
            return;
        }
        // Tokenize.
        token = strtok(buf, " \t\r\n\v\f");

        while (token != NULL) {
            printf("%s\n", token);
            token = strtok(NULL, " \t\r\n\v\f");
        }
    }

}

// Simple Shell Implementation.
int main() {
    inputLoop(); 
}
