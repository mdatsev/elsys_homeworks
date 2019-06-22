//------------------------------------------------------------------------
// NAME: Martin Datsev
// CLASS: XIb
// NUMBER: 17
// PROBLEM: #1
// FILE NAME: tail.c
// FILE PURPOSE:
// prints last 10 lines of file(s)
// (or the whole files if < 10 lines)
// if argument "-" is given or no arguments it reads from STDIN
//------------------------------------------------------------------------

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

//------------------------------------------------------------------------
// FUNCTION: print
// prints the filename surrounded with 2 strings and returns the result of write
// PARAMETERS:
// prefix - string inserted before the filename
// filename - middle string
// postfix - string inserted after the filename
//------------------------------------------------------------------------
int print(const char *prefix, const char *filename, const char *postfix)
{
    char str[512];
    strcpy(str, prefix);
    strcat(str, filename);
    strcat(str, postfix);
    return write(STDOUT_FILENO, str, strlen(str));
}

//------------------------------------------------------------------------
// FUNCTION: print_err
// calls perror with the filename surrounded with 2 strings
// PARAMETERS:
// prefix - string inserted before the filename
// filename - middle string
// postfix - string inserted after the filename
//------------------------------------------------------------------------
void print_err(const char *prefix, const char *filename, const char *postfix)
{
    char err[512];
    strcpy(err, prefix);
    strcat(err, filename);
    strcat(err, postfix);
    perror(err);
}

//------------------------------------------------------------------------
// FUNCTION: main
// entry point
// PARAMETERS:
// argc - number of arguments
// argv - array of arguments
//------------------------------------------------------------------------
int main(int argc, char **argv)
{
    int prevent_newline = 0;
    int stdin = argc == 1;
    char *stdinstr = "-";
    int write_error = 0;
    for (int i = 0; i < argc - 1 || stdin; i++)
    {
        int total_lines = 10;
        const char *filename = stdin ? stdinstr : argv[i + 1];
        if (filename[0] == '-' && filename[1] == '\0')
        {
            stdin = 0;
            int size = 10;
            char *buffer = malloc(size * sizeof(char));
            int i = 0;
            char *lines[total_lines + 1];
            int nlines = 0;
            while (1)
            {
                ssize_t redd = read(STDIN_FILENO, &buffer[i], 1);
                if (buffer[i] == '\n')
                {
                    nlines++;
                    for (int i = 0; i < total_lines; i++)
                    {
                        lines[i] = lines[i + 1];
                    }
                    lines[total_lines] = &buffer[i + 1];
                }
                i++;
                if (redd == 0)
                {
                    break;
                }
                if (i == size)
                {
                    size *= 2;
                    buffer = realloc(buffer, size * sizeof(char));
                }
            }
            if (nlines < total_lines)
            {
                lines[0] = buffer;
            }
            if (write(STDOUT_FILENO, lines[0], buffer + i - lines[0] - 1) < 0)
            {
                perror("tail: error writing");
            }
            continue;
        }
        int fd = open(filename, O_RDONLY);
        if (fd < 0)
        {
            print_err("tail: cannot open '", filename, "' for reading");
            if (i == 0)
            {
                prevent_newline = 1;
            }
            continue;
        }
        int result = 0;
        if (argc > 2)
        {
            if (i == 0 || prevent_newline)
                result = print("==> ", filename, " <==\n");
            else
                result = print("\n==> ", filename, " <==\n");
        }
        if (result < 0)
        {
            write_error = 1;
        }
        prevent_newline = 0;
        char c = '0';
        lseek(fd, -1, SEEK_END);
        if (read(fd, &c, 1) < 0)
        {
            print_err("tail: error reading '", filename, "'");
            continue;
        }
        if (c == '\n')
            total_lines++;
        off_t filesize = lseek(fd, 0, SEEK_END);
        if (filesize > 0)
        {
            char c = '0';
            lseek(fd, -1, SEEK_END);
            ssize_t redd = 0;
            do
            {
                redd = read(fd, &c, 1);
                if (redd < 0)
                {
                    print_err("tail: error reading '", filename, "'");
                    continue;
                }
            } while (redd == 0);
        }
        int lines_found = 0;
        int j = 0;
        for (; j < filesize + 1 && lines_found < total_lines; j++)
        {
            lseek(fd, -j - 1, SEEK_END);
            while (read(fd, &c, 1) == 0 && j < filesize)
            {
                read(fd, &c, 1);
            }
            if (c == '\n')
                lines_found++;
        }
        lseek(fd, -j + 1, SEEK_END);
        while (read(fd, &c, 1) > 0)
        {
            ssize_t written = 0;
            while (written == 0)
            {
                written = write(STDOUT_FILENO, &c, 1);
                if (written < 0)
                {
                    write_error = 1;
                    break;
                }
            }
        }
        if (close(fd) < 0)
        {
            print_err("tail: error reading '", filename, "'");
        }
    }
    if (write_error)
    {
        perror("tail: error writing");
    }
    return 0;
}