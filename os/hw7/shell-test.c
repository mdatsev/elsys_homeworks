#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    char *line = NULL;
    size_t len = 0;
    while (1)
    {
        ssize_t read = getline(&line, &len, stdin);
        if (read <= 0 || feof(stdin))
            break;
        puts(line);
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
            exit(-1);
        }
        if (pid == 0)
        {
            _exit(0);
        }
        else
        {
            //wait(NULL);
            waitpid(pid, 0, 0);
        }
    }
    return 0;
}