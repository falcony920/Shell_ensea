#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include "utils.h"
#include "code_command.h"
#include "redirection.h" // Include redirection header

#define UNKNOWN_CMD "Unknown command, please retry\n"
#define ERROR_FORK "Failed to fork\n"

void execute_command(const char *input)
{
    char *command = strdup(input);
    char *args[100];
    int i = 0;

    // Tokenize input for command and arguments
    args[i++] = strtok(command, " ");
    while ((args[i++] = strtok(NULL, " ")) != NULL)
        ;

    pid_t pid = fork();
    if (pid == -1)
    {
        write(STDOUT_FILENO, ERROR_FORK, strlen(ERROR_FORK));
    }
    else if (pid == 0)
    {
        // Handle I/O redirection in the child process
        if (handle_output_redirection(args) == -1 || handle_input_redirection(args) == -1)
        {
            exit(1);
        }

        execvp(args[0], args); // Execute command
        write(STDOUT_FILENO, UNKNOWN_CMD, strlen(UNKNOWN_CMD));
        exit(1);
    }
    else
    {
        struct timespec start_time, end_time;
        clock_gettime(CLOCK_MONOTONIC, &start_time);

        int status;
        waitpid(pid, &status, 0);

        clock_gettime(CLOCK_MONOTONIC, &end_time);
        display_command_status(status, start_time, end_time);
    }

    free(command);
}
