#include "custom.h"
#include <stdlib.h>

static int cd_custom (int argc, char **argv) {
    if (argc != 2) {
        printf("sshell: cd got too many arguments\n");
        return CUSTOM_FAIL;
    }
    if(chdir(argv[1]) == -1) {
        printf("sshell: cd failed to change to directory %s\n", argv[1]);
        return CUSTOM_FAIL;
    }
    return CUSTOM_SUCCESS;
}

static int exit_custom (int argc, char **argv) {
    if (argc > 2) {
        printf("sshell: exit got too many arguments\n");
        return CUSTOM_FAIL;
    }
    // TODO: add handling for custom exit codes.
    exit(EXIT_SUCCESS);
    return CUSTOM_SUCCESS;
}

static custom_command custom[] = {
    {"cd",cd_custom},
    {"exit", exit_custom}
};

// Handle custom commands.
// Return Codes:
// 0 -> handled
// 1 -> no match found
// -1 -> error when executing.
int8_t handleCustom(int argc, char *argv[]) {
    for (int i = 0; i < NUM_CUSTOM; ++i) {
        if (strcmp(argv[0], custom[i].name) == 0) {
            return custom[i].func(argc, argv);
        }
    }
    return CUSTOM_NOMATCH; // No Match Found.
}
