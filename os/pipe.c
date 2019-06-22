#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    int flides[2];
    const char *message = "Hello World";
    char buffer[256];

    if (pipe(flides))
    {
        perror("pipe");
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
    }
    else if (pid == 0)
    {
        printf("Hello from child\n");
        close(flides[0]);
        write(flides[1], message, strlen(message) + 1);
    }
    else
    {
        waitpid(pid, 0, 0);
        printf("Hello from parent\n");
        close(flides[1]);
        read(flides[0], buffer, sizeof(buffer));
        printf("Message: %s", buffer);
    }
    return 0;
}