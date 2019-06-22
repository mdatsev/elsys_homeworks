#include <stdio.h>
#include <stdint.h>
void *read_image( const char *filepath );

int main(int argc, char** argv)
{
    int8_t* ptr = read_image(argv[1]);
    printf("BMP image width: %d\n", *(int32_t*)(ptr + 18));
    printf("BMP image height: %d\n", *(int32_t*)(ptr + 22));
    return 0;
}