#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <pwd.h>
int main(int argc, char **argv)
{
    struct stat st;
    for (int i = 1; i < argc; i++)
    {
        stat(argv[i], &st);
        printf("%s %s\n", argv[i], getpwuid(st.st_uid)->pw_name);
    }
}