#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "utils.h"
#include "code_command.h"

#include <sys/wait.h>

#define UNKNOWN_CMD "Unknown command, please retry\n"
#define ERROR_FORK "Failed to fork\n"

void execute_command(const char *command)
{
    // Create a new process to run the command entered by the user
    pid_t pid = fork();
    if (pid == -1)
    {
        // Handle error in fork
        write(STDOUT_FILENO, ERROR_FORK, 15);
    }
    else if (pid == 0)
    {
        // In child process
        execlp(command, command, (char *)NULL);

        // If execlp fails (command not found), print error
        write(STDOUT_FILENO, UNKNOWN_CMD, 30);
        exit(1); // Exit the child process
    }

    else
    {
        // In parent process, wait for the child to complete
        int status;
        waitpid(pid, &status, 0); // Wait for child to finish

        display_command_status(status);
    }
}
