#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    int i;
    char *p = 0x10000;
    for (i = 0; i < 1000000; i++)
    {
        *p++ = 0;
    }
}