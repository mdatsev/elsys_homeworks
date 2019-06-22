#define _GNU_SOURCE
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define LINES 10
#define BUFFER_SIZE 1

void print_header(const char *filename)
{
    //char *header;
    //asprintf(&header, "\n===> %s <===\n", filename);
    write(STDOUT_FILENO, "==> ", 4);
    write(STDOUT_FILENO, filename, strlen(filename));
    //write(STDOUT_FILENO, header, strlen(header));
    write(STDOUT_FILENO, " <==\n", 5);
    //free(header);
}

int print_tail(const char *file, int print_head, int lines_total, int newline)
{
    if (file[0] == '-')
    {
        int size = 10;
        char *buffer = malloc(size * sizeof(char));
        int i = 0;
        char *lines[lines_total + 1];
        int nlines = 0;
        while (1)
        {
            ssize_t redd = read(STDIN_FILENO, &buffer[i], 1);
            if (buffer[i] == '\n')
            {
                nlines++;
                for (int i = 0; i < lines_total; i++)
                {
                    lines[i] = lines[i + 1];
                }
                lines[lines_total] = &buffer[i + 1];
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
        if (nlines < lines_total)
        {
            lines[0] = buffer;
        }
        if (write(STDOUT_FILENO, lines[0], buffer + i - lines[0] - 1) < 0)
        {
            perror("tail: error writing");
            return 1;
        }
        return 0;
    }
    char c;

    int fd = file[0] != '-' ? open(file, O_RDONLY) : dup(STDIN_FILENO);
    if (fd < 0)
    {
        char err[512] = "tail: cannot open '";
        strcat(err, file);
        strcat(err, "' for reading");
        //asprintf(&error, "tail: cannot open %s for reading", file);
        perror(err);
        //free(error);
        return 1;
    }
    else if (newline)
    {
        //write(1, "in", 2);
        if (write(1, "\n", 1) < 0)
        {
            perror("tail: error writing");
        }
    }
    if (print_head)
    {
        print_header(file);
    }
    lseek(fd, -1, SEEK_END);
    if (read(fd, &c, 1) < 0)
    {
        char err[512] = "tail: error reading '";
        strcat(err, file);
        strcat(err, "'");
        //asprintf(&error, "tail: cannot open %s for reading", file);
        perror(err);
    }
    if (c == '\n')
    {
        lines_total++;
    }
    off_t size = lseek(fd, 1, SEEK_END) - 1;

    //write(1, "\n", 1);
    for (int i = 0, bytes = 0; i < lines_total;)
    {
        if (bytes >= size)
        {
            lseek(fd, -1, SEEK_CUR);
            break;
        }
        bytes++;
        lseek(fd, -2, SEEK_CUR);
        if (read(fd, &c, 1) < 0)
        {
            perror("read");
            return 3;
        }
        if (c == '\n')
            i++;
    }
    for (int i = 0; i < lines_total;)
    {
        ssize_t read_bytes = read(fd, &c, 1);
        if (read_bytes < 0)
        {
            char err[512] = "tail: error reading '";
            strcat(err, file);
            strcat(err, "'");
            //asprintf(&error, "tail: cannot open %s for reading", file);
            perror(err);
            //free(error);
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
            perror("tail: error writing");
            return 4;
        }
    }
    if (close(fd) < 0)
    {
        perror("close");
        return 2;
    }
    if (size > 0)
    {
        //write(1, "\n", 1);
    }
}

int main(int argc, char **argv)
{
    if (argc == 1)
    {
        print_tail("-", argc > 2, LINES, 0);
    }
    int newl = 1;
    for (int i = 0; i < argc - 1; i++)
    {
        const char *filename = argv[i + 1];
        //write(1, "*", 1);
        if (newl)
        {
            newl = print_tail(filename, argc > 2, LINES, !newl);
            continue;
        }
        print_tail(filename, argc > 2, LINES, !newl);
    }
    return 0;
}