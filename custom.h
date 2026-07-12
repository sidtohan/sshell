#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <linux/limits.h>

#define NUM_CUSTOM 3
#define CUSTOM_FAIL -1
#define CUSTOM_SUCCESS 0
#define CUSTOM_NOMATCH 1

extern int8_t handleCustom(int argc, char *argv[]); 
typedef struct {
    char *name;
    int (*func)(int argc, char **argv);
} custom_command;
