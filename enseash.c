#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
    // Display welcome message
    write(STDOUT_FILENO, "Welcome to ENSEA Tiny Shell.\nType 'exit' to quit.\nenseash % ", 60);

    char command[256];
    while (1)
    {
        // Read user input
        ssize_t n = read(STDIN_FILENO, command, sizeof(command) - 1);
        if (n <= 0)
            break;

        // Remove newline character
        command[n - 1] = '\0';

        // Exit condition
        if (strcmp(command, "exit") == 0)
        {
            write(STDOUT_FILENO, "Bye bye...\n", 11);
            break;
        }

        // Display prompt again
        write(STDOUT_FILENO, "enseash % ", 10);
    }
    return 0;
}
