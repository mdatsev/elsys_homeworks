#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>
#include </usr/include/linux/fcntl.h>
#include <stdbool.h>

int debug_count = 0;

void ftrace(const char *format, ...)
{
    va_list valist;
    /* initialize valist for num number of arguments */
    char stamp[1024];
    sprintf(stamp, "%d\t%s\n", getpid(), format);
    va_start(valist, format);
    for (;;)
    {
        FILE *fd;
        if (fd = fopen("trace.log", "a"))
        {
            vfprintf(fd, stamp, valist);
            fclose(fd);
            break;
        }
        usleep(10000);
    }
    va_end(valist);
}

char **split(const char *line, char delimiter, int *size)
{

    const char *start = line;
    for (int i = 0; line[i] == delimiter; i++)
    {
        start = &line[i + 1];
    }
    char *mutable = malloc((strlen(start) + 1) * sizeof(char));
    if (mutable == NULL)
    {
        printf("no memory alloc");
        exit(-1);
    }
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
            if (result == NULL)
            {
                printf("no memory realloc");
                exit(-1);
            }
            result[argc - 1] = beginning;
            beginning = cur + 1;
            if (*cur == '\0')
                break;
            *cur = '\0';
        }
    }

    ftrace("%d", argc);
    result[argc] = NULL;
    if (size)
    {
        *size = argc;
    }
    return result;
}

char **parse_cmdline(const char *line)
{
    debug_count++;
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
        if (feof(stdin))
            break;
        if (empty(line))
            continue;
        line[read - 1] = '\0';
        int commands_count;
        char **commands = parse_pipes(line, &commands_count);
        pid_t pids[commands_count];
        int pipefds[2];
        for (int i = 0; commands[i] != NULL; i++)
        {
            char **cmdargv = parse_cmdline(commands[i]);
            int prev_pipe_read = pipefds[0];
            int prev_pipe_write = pipefds[1];
            if (i != commands_count - 1)
            {
                pipe(pipefds);
                //int ret = fcntl(pipefds[1], F_SETPIPE_SZ, getpagesize());
            }
            pids[i] = fork();
            if (pids[i] < 0)
            {
                perror("fork");
            }
            else if (pids[i] == 0)
            {
                if (i != 0)
                {
                    //ftrace("closing prev_pipe_write = %d", prev_pipe_write);
                    close(prev_pipe_write);
                    dup2(prev_pipe_read, STDIN_FILENO);
                    //ftrace("dup %d, prev_pipe_read = %d", dup2(prev_pipe_read, STDIN_FILENO), prev_pipe_read);
                }
                if (i != commands_count - 1)
                {
                    //ftrace("closing pipefds[0](read) = %d", pipefds[0]);
                    close(pipefds[0]);
                    dup2(pipefds[1], STDOUT_FILENO);
                    //ftrace("dup %d, pipefds[1](write) = %d", dup2(pipefds[1], STDOUT_FILENO), pipefds[1]);
                }
                if (execvp(cmdargv[0], cmdargv) < 0)
                {
                    perror(cmdargv[0]);
                    free(cmdargv[0]);
                    free(cmdargv);
                    free(line);
                    free(commands[0]);
                    free(commands);
                    exit(-1);
                }
            }
            if (i != commands_count - 1)
            {
                //ftrace("closing pipefds[1](write) = %d", pipefds[1]);
                close(pipefds[1]);
            }
            //close(pipefds[0]);
            //printf("%p %p %p", cmdargv, cmdargv[0], line);
            free(cmdargv[0]);
            free(cmdargv);
        }
        for (int i = 0; i < commands_count; i++)
        {
            int status;
            waitpid(pids[i], &status, 0);
            //wait(NULL);
            //ftrace("process %d terminated", pids[i]);
            if (status)
            {
                //?
            }
        }
        free(commands[0]);
        free(commands);
    }
    free(line);
    return 0;
}