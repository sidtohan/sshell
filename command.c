#include "command.h"

static int cd_custom(int argc, char **argv) {
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

static int exit_custom(int argc, char **argv) {
    if (argc > 2) {
        printf("sshell: exit got too many arguments\n");
        return CUSTOM_FAIL;
    }
    // TODO: add handling for custom exit codes.
    exit(EXIT_SUCCESS);
    return CUSTOM_SUCCESS;
}

static int pwd_custom(int argc, char **argv) {
    char buf[PATH_MAX];
    if (getcwd(buf, sizeof(buf)) == NULL) {
        printf("sshell: couldn't list current working directory");
        return CUSTOM_FAIL;
    }
    printf("%s\n", buf);
    return CUSTOM_SUCCESS;
}

static custom_command custom[] = {
    {"cd",cd_custom},
    {"exit", exit_custom},
    {"pwd", pwd_custom}
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

void executeCommand(char *command, int argc, char *argv[], int8_t redirect, char *redirect_fname) {
    int pid;
    // For most commands, will prefer external implementation for now.
    // For cd, will use chdir.
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
            char *filename = redirect_fname;
            int o_flags = (redirect & (2) ? O_APPEND : O_TRUNC);
            fd = open(filename, O_WRONLY | O_CREAT | o_flags, S_IWUSR | S_IRUSR);
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
