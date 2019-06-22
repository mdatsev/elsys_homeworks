#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 100

int main(int argc, char **argv)
{
    char buffer[SIZE];

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("open");
        return 1;
    }
    lseek(fd, 0, SEEK_END);
    read return 0;
}