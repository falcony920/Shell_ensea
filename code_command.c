#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include "utils.h"

#define UNKNOWN_CMD "Unknown command, please retry\n"

// Function to display the status of the previous command
void display_command_status(int status, struct timespec start_time, struct timespec end_time)
{
    // Calculate execution time in milliseconds
    long long start_ns = start_time.tv_sec * 1000000000L + start_time.tv_nsec;
    long long end_ns = end_time.tv_sec * 1000000000L + end_time.tv_nsec;
    long long elapsed_ns = end_ns - start_ns;
    long long elapsed_ms = elapsed_ns / 1000000L;

    // Handle the exit status or signal
    if (WIFEXITED(status))
    {
        // If the command executed successfully, show its exit code
        int exit_code = WEXITSTATUS(status);
        char exit_code_msg[50];
        exit_code_msg[0] = '\0';

        // Convert exit code to string
        snprintf(exit_code_msg, sizeof(exit_code_msg), "%d", exit_code);

        if (exit_code == 0)
        {
            // Display exit code and execution time in milliseconds
            write(STDOUT_FILENO, "enseash [exit:0|", 15);
            char time_msg[50];
            snprintf(time_msg, sizeof(time_msg), "|%lldms", elapsed_ms);
            write(STDOUT_FILENO, time_msg, strlen(time_msg));
            write(STDOUT_FILENO, "] %  ", 5);
        }
        else
        {
            // Display non-zero exit code and execution time
            write(STDOUT_FILENO, "enseash [exit:", 14);
            write(STDOUT_FILENO, exit_code_msg, strlen(exit_code_msg));
            // write(STDOUT_FILENO, "|", 1);
            char time_msg[50];
            snprintf(time_msg, sizeof(time_msg), "|%lldms", elapsed_ms);
            write(STDOUT_FILENO, time_msg, strlen(time_msg));
            write(STDOUT_FILENO, "] %  ", 5);
        }
    }
    else if (WIFSIGNALED(status))
    {
        // If the process was terminated by a signal
        int signal = WTERMSIG(status);
        char signal_msg[50];
        snprintf(signal_msg, sizeof(signal_msg), "%d", signal);

        // Display signal number and execution time
        write(STDOUT_FILENO, "enseash [sign:", 14);
        write(STDOUT_FILENO, signal_msg, strlen(signal_msg));
        // write(STDOUT_FILENO, "|", 1);
        char time_msg[50];
        snprintf(time_msg, sizeof(time_msg), "|%lldms", elapsed_ms);
        write(STDOUT_FILENO, time_msg, strlen(time_msg));
        write(STDOUT_FILENO, "] %  ", 5);
    }
}
