#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

#define MAX_CMD_LENGTH 1024
#define MAX_ARGS 100

void parse_command(char *cmd, char **args)
{
    char *token;
    int i = 0;

    token = strtok(cmd, " \t\n");
    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

int main()
{
    char *cmd;
    char *args[MAX_ARGS];
    pid_t pid;
    int status;

    printf("Welcome to MyShell! Type 'exit' to quit.\n");

    while (1)
    {
        cmd = readline("MyShell> ");
        if (cmd == NULL)
        {
            printf("\n");
            break; // Exit on EOF (Ctrl+D)
        }

        if (strlen(cmd) == 0)
        {
            free(cmd);
            continue; // Ignore empty commands
        }

        add_history(cmd);

        if (strcmp(cmd, "exit") == 0)
        {
            free(cmd);
            break; // Exit command
        }

        parse_command(cmd, args);

        pid = fork();
        if (pid < 0)
        {
            perror("Fork failed");
            free(cmd);
            continue;
        }
        else if (pid == 0)
        {
            // Child process
            // Try executing the command directly (system path)
            if (execvp(args[0], args) < 0)
            {
                // If failed and command doesn't contain '/', try current directory
                if (strchr(args[0], '/') == NULL)
                {
                    char local_cmd[MAX_CMD_LENGTH];
                    snprintf(local_cmd, sizeof(local_cmd), "./%s", args[0]);
                    // We need to update args[0] to point to the new path for the process name
                    args[0] = local_cmd;
                    execvp(args[0], args);
                }
                
                // If still failed (or second execvp failed)
                perror("Execution failed");
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            // Parent process
            waitpid(pid, &status, 0);
        }

        free(cmd);
    }
}