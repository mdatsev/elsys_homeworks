#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    char *buf = NULL;
    size_t size = 0;
    while (1)
    {
        int read = getline(&buf, &size, stdin);
        if (read <= 0 || feof(stdin))
        {
            break;
        }
    }
}