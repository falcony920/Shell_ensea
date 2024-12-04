#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "redirection.h"

// Macros for error messages
#define ERR_NO_OUTPUT_FILE "Error: No output file specified.\n"
#define ERR_NO_INPUT_FILE "Error: No input file specified.\n"

// Function: Handle output redirection using '>'
// Redirects standard output to the specified file
int handle_output_redirection(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], ">") == 0)
        {
            // Ensure the file name is provided after '>'
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, ERR_NO_OUTPUT_FILE);
                return -1;
            }
            // Redirect stdout to the specified file (overwrites if exists)
            if (freopen(args[i + 1], "w", stdout) == NULL)
            {
                perror("Error redirecting output");
                return -1;
            }
            // Nullify the redirection operator and file name in the argument list
            args[i] = NULL;
            return 0;
        }
    }
    return 1; // No redirection operator found
}

// Function: Handle input redirection using '<'
// Redirects standard input from the specified file
int handle_input_redirection(char **args)
{
    for (int i = 0; args[i] != NULL; i++)
    {
        if (strcmp(args[i], "<") == 0)
        {
            // Ensure the file name is provided after '<'
            if (args[i + 1] == NULL)
            {
                fprintf(stderr, ERR_NO_INPUT_FILE);
                return -1;
            }
            // Redirect stdin from the specified file
            if (freopen(args[i + 1], "r", stdin) == NULL)
            {
                perror("Error redirecting input");
                return -1;
            }
            // Nullify the redirection operator and file name in the argument list
            args[i] = NULL;
            return 0;
        }
    }
    return 1; // No redirection operator found
}
