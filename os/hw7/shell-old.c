#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdbool.h>

char **split(const char *line, char delimiter, int *size)
{

    const char *start = line;
    for (int i = 0; line[i] == delimiter; i++)
    {
        start = &line[i + 1];
    }
    char *mutable = malloc((strlen(start) + 1) * sizeof(char));
    strcpy(mutable, start);
    char **result = NULL;
    int argc = 0;
    char *beginning = &mutable[0];
    int result_size = 128;
    for (char *cur = &mutable[0];; cur++)
    {
        if (*cur == delimiter || *cur == '\0')
        {
            if (cur - beginning == 0)
            {
                beginning = cur + 1;
                if (*cur == '\0')
                    break;
                else
                    continue;
            }
            argc++;

            if (argc + 1 > result_size)
                result_size *= 2;
            result = realloc(result, result_size * sizeof(char *));
            result[argc - 1] = beginning;
            beginning = cur + 1;
            if (*cur == '\0')
                break;
            *cur = '\0';
        }
    }

    result[argc] = NULL;
    if (size)
    {
        *size = argc;
    }
    return result;
}

char **parse_cmdline(const char *line)
{
    return split(line, ' ', NULL);
}

char **parse_pipes(const char *line, int *size)
{
    return split(line, '|', size);
}

bool empty(const char *str)
{
    for (const char *c = str; *c != '\0'; c++)
    {
        if (*c != ' ' && *c != '\n' && *c != '|' && *c != '\t')
            return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t read = 0;
    while (1)
    {
        write(STDOUT_FILENO, "$ ", 2);
        read = getline(&line, &len, stdin);

        if (read <= 0 || feof(stdin))
            break;
        if (empty(line))
            continue;
        if (line[read - 1] == '\n')
            line[read - 1] = '\0';
        int commands_count;
        char **commands = parse_pipes(line, &commands_count);
        int pipefds[2];
        for (int i = 0; commands[i] != NULL; i++)
        {
            char **cmdargv = parse_cmdline(commands[i]);
            int prev_pipe_read = pipefds[0];
            int prev_pipe_write = pipefds[1];
            if (i != commands_count - 1)
            {
                pipe(pipefds);
            }
            pid_t pid = fork();
            if (pid < 0)
            {
                perror("fork");
            }
            else if (pid == 0)
            {
                if (i != 0)
                {
                    dup2(prev_pipe_read, STDIN_FILENO);
                    close(prev_pipe_read);
                    close(prev_pipe_write);
                }
                if (i != commands_count - 1)
                {

                    dup2(pipefds[1], STDOUT_FILENO);
                    close(pipefds[0]);
                    close(pipefds[1]);
                }
                if (execvp(cmdargv[0], cmdargv))
                {
                    perror(cmdargv[0]);
                    free(cmdargv[0]);
                    free(cmdargv);
                    free(line);
                    free(commands[0]);
                    free(commands);
                    exit(0);
                }
            }
            if (i != 0)
            {
                close(prev_pipe_read);
                close(prev_pipe_write);
            }

            free(cmdargv[0]);
            free(cmdargv);
        }
        for (int i = 0; i < commands_count; i++)
        {
            wait(NULL);
        }
        free(commands[0]);
        free(commands);
    }
    free(line);
    return 0;
}