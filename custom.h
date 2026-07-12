#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define NUM_CUSTOM 2
#define CUSTOM_FAIL -1
#define CUSTOM_SUCCESS 0
#define CUSTOM_NOMATCH 1

extern int8_t handleCustom(int argc, char *argv[]); 
typedef struct {
    char *name;
    int (*func)(int argc, char **argv);
} custom_command;
