#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>

#define SIZE 100
#define filename1 "chatfifo1"
#define filename2 "chatfifo2"

int main()
{
    int rd, wr;
    bool first = (access(filename1, F_OK) == -1);
    if (first)
    {
        mkfifo(filename1, S_IRUSR | S_IWUSR);
        wr = open(filename1, O_RDWR);
        while ((rd = open(filename2, O_RDWR)) < 0)
            ;
    }
    else
    {
        rd = open(filename1, O_RDWR);
        mkfifo(filename2, S_IRUSR | S_IWUSR);
        wr = open(filename2, O_RDWR);
    }

    fcntl(rd, F_SETFL, O_NONBLOCK);
    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

    ssize_t stdin_read_bytes, fifo_read_bytes;
    char stdin_read_buf[SIZE], fifo_read_buf[SIZE];
    while ((stdin_read_bytes = read(STDIN_FILENO, stdin_read_buf, SIZE)) != 0 &&
           (fifo_read_bytes = read(rd, fifo_read_buf, SIZE)) != 0)
    {
        write(wr, stdin_read_buf, stdin_read_bytes);
        write(STDOUT_FILENO, fifo_read_buf, fifo_read_bytes);
    }
    remove(first ? filename1 : filename2);
}