

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void execute_piped_command(const char *input)
{
    char *command = strdup(input);
    char *left_cmd = strtok(command, "|");
    char *right_cmd = strtok(NULL, "|");

    if (right_cmd == NULL)
    {
        fprintf(stderr, "Error: No command after pipe\n");
        free(command);
        return;
    }

    int pipefd[2];
    if (pipe(pipefd) == -1)
    {
        perror("Pipe failed");
        free(command);
        return;
    }

    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        // First child process (Left command)
        close(pipefd[0]);               // Close read end
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to write end of pipe
        close(pipefd[1]);

        char *args[100];
        args[0] = strtok(left_cmd, " ");
        for (int i = 1; (args[i] = strtok(NULL, " ")) != NULL; i++)
            ;

        execvp(args[0], args);
        perror("Exec failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        // Second child process (Right command)
        close(pipefd[1]);              // Close write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to read end of pipe
        close(pipefd[0]);

        char *args[100];
        args[0] = strtok(right_cmd, " ");
        for (int i = 1; (args[i] = strtok(NULL, " ")) != NULL; i++)
            ;

        execvp(args[0], args);
        perror("Exec failed");
        exit(EXIT_FAILURE);
    }

    // Parent process
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    free(command);
}
