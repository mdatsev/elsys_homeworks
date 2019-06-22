#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int count = atoi(argv[1]);
    for (int i = 0; i < count; i++)
    {
        pid_t pid = fork();
        if (pid < 0)
        {
            perror("fork");
        }
        else if (pid == 0)
        {
            if (execv(argv[2], &argv[2]) < 0)
            {
                char buffer[512] = "multifork: ";
                strcat(buffer, argv[2]);
                perror(buffer);
                return 1;
            };
        }
        else
        {
            int status;
            waitpid(pid, &status, 0);
            int error = WEXITSTATUS(status);
            if (error)
            {
                break;
            }
        }
    }
    /*
    //parallel
    for (int i = 0; i < count; i++)
    {
        wait(NULL);
    }
    */
}