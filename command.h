#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <linux/limits.h>
#include <sys/wait.h>

#define NUM_CUSTOM 3
#define CUSTOM_FAIL -1
#define CUSTOM_SUCCESS 0
#define CUSTOM_NOMATCH 1

extern int8_t handleCustom(int argc, char *argv[]); 
void executeCommand(char *command, int argc, char *argv[], int8_t redirect, char *redirect_fname); 
typedef struct {
    char *name;
    int (*func)(int argc, char **argv);
} custom_command;
