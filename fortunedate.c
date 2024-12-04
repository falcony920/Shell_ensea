#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"
#include "code_command.h"

#include <sys/wait.h>

#define UNKNOWN_CMD "Unknown command, please retry\n"
#define ERROR_FORK "Failed to fork\n"

void execute_command(const char *input)
{
    // Tokenize the input command to handle arguments
    char *command = strdup(input);
    char *args[100];
    int i = 0;

    args[i++] = strtok(command, " "); // First token is the command
    while ((args[i++] = strtok(NULL, " ")) != NULL)
        ; // Remaining tokens are arguments

    pid_t pid = fork();
    if (pid == -1)
    {
        // Handle error in fork
        write(STDOUT_FILENO, ERROR_FORK, strlen(ERROR_FORK));
    }
    else if (pid == 0)
    {
        // In child process: execute the command with arguments
        execvp(args[0], args);

        // If execvp fails (command not found), print error
        write(STDOUT_FILENO, UNKNOWN_CMD, strlen(UNKNOWN_CMD));
        exit(1); // Exit the child process
    }
    else
    {
        // In parent process, wait for the child to complete
        int status;
        waitpid(pid, &status, 0); // Wait for child to finish
        display_command_status(status);
    }

    free(command); // Free the duplicated string
}
