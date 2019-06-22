//------------------------------------------------------------------------
// NAME: Martin Datsev
// CLASS: XIb
// NUMBER: 17
// PROBLEM: #1
// FILE NAME: seek.c
// FILE PURPOSE:
// prints out a part of a file
// where the first argument is the name of the file
// the second is how many bytes to skip and the third how many bytes to print
//------------------------------------------------------------------------

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

int main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDONLY);
    lseek(fd, atoi(argv[2]), SEEK_SET);
    int size = atoi(argv[3]);
    char buffer[BUFFER_SIZE];
    ssize_t totalr = 0;
    while (totalr < size)
    {
        ssize_t redd = read(fd, buffer, size < BUFFER_SIZE ? size : BUFFER_SIZE);
        if (redd == 0)
            break;
        totalr += redd;
        ssize_t totalw = 0;
        while (totalw < redd)
        {
            totalw += write(STDOUT_FILENO, buffer, redd);
        }
    }
    close(fd);
}