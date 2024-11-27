#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "fortunedate.h"

#define WELCOME_MSG "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\nenseash % "
#define FORTUNE_CMD "fortune"
#define DATE_CMD "date"
#define EXIT_CMD "exit"
#define EXIT_MSG "Bye bye...\n"
#define UNKNOWN_CMD "Unknown command, please retry\n"

int main()
{
    // It writes the message to the standard output (STDOUT).
    write(STDOUT_FILENO, WELCOME_MSG, 60);

    char command[128]; // Buffer to hold the user input

    while (1)
    {
        // We read from the standard input (STDIN) and store it in the 'command' buffer.
        ssize_t n = read(STDIN_FILENO, command, sizeof(command) - 1);

        // 'read' returns the number of bytes read. If the user input is invalid (n <= 0),
        // we break out of the loop.
        if (n <= 0)
            break;

        // The 'read' function leaves a newline character at the end of the user input,
        // so we remove it manually by replacing it with a null terminator.
        // This ensures the command string is properly formatted without extra newlines.
        command[n - 1] = '\0';

        // 'strcmp' function compares two strings.
        // If the strings match, it returns 0, indicating the user typed 'exit'.
        if (strcmp(command, EXIT_CMD) == 0)
        {
            write(STDOUT_FILENO, EXIT_MSG, 11);
            break;
        }
        // Replace the previous command execution logic with this:
        else
        {
            execute_command(command);
        }

        write(STDOUT_FILENO, "enseash % ", 10);
    }

    return 0;
}
