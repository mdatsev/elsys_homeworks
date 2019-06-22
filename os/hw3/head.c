#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define LINES 10

int main(int argc, char **argv)
{
    char c;

    int fd = open("a.txt", O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }

    for (int i = 0; i < LINES;)
    {
        ssize_t read_bytes = read(fd, &c, 1);
        if (read_bytes < 0)
        {
            perror("read");
            return 3;
        }
        else if (read_bytes == 0)
        {
            break;
        }
        if (c == '\n')
            i++;
        if (write(STDOUT_FILENO, &c, 1) < 0)
        {
            perror("write");
            return 4;
        }
    }
    if (close(fd) < 0)
    {
        perror("close");
        return 2;
    }
    return 0;
}