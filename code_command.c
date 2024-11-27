// command_status.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "utils.h"

#define UNKNOWN_CMD "Unknown command, please retry\n"

// Function to display the status of the previous command
void display_command_status(int status)
{
    if (WIFEXITED(status))
    {
        // If the command executed successfully, show its exit code
        int exit_code = WEXITSTATUS(status);
        char exit_code_msg[50];
        exit_code_msg[0] = '\0';

        // Convert exit code to string using itoa
        itoa(exit_code, exit_code_msg);

        if (exit_code == 0)
        {
            write(STDOUT_FILENO, "enseash [exit:0] % ", 18);
        }
        else
        {
            write(STDOUT_FILENO, "enseash [exit:", 14);
            write(STDOUT_FILENO, exit_code_msg, strlen(exit_code_msg));
            write(STDOUT_FILENO, "] % ", 4);
        }
    }
    else if (WIFSIGNALED(status))
    {
        // If the process was terminated by a signal
        int signal = WTERMSIG(status);
        char signal_msg[50];
        signal_msg[0] = '\0';

        // Convert signal number to string
        itoa(signal, signal_msg);

        write(STDOUT_FILENO, "enseash [sign:", 14);
        write(STDOUT_FILENO, signal_msg, strlen(signal_msg));
        write(STDOUT_FILENO, "] % ", 4);
    }
}
