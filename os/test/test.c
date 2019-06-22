#include <unistd.h>
#include <stdio.h>

int main()
{
    write(STDOUT_FILENO, "1.", 2);
    printf("2.");
    write(STDOUT_FILENO, "3.", 2);
    printf("4.\n5.");
    printf("6.");
    write(STDOUT_FILENO, "7.", 2);
}