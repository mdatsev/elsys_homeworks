#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>

void *read_image( const char *filepath );

int main(int argc, char** argv)
{
    int8_t* ptr = read_image(argv[1]);
    int8_t* start = ptr;
    if(!ptr)
    {
        printf("Unable to open file");
        return;
    }
    if(strncmp( (const char*)ptr, "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A", 8 ))
    {
        printf("Unable to parse file");
        return;
    }

    ptr += 8;

    printf("PNG image width: %d\n", ntohl(*(uint32_t*)(ptr + 8)));
    printf("PNG image height: %d\n", ntohl(*(uint32_t*)(ptr + 12)));

    while(strncmp( (const char*)(ptr + 4), "\x49\x45\x4E\x44", 4))
    {
        uint32_t len = ntohl(*(uint32_t*)ptr);
        ptr += 4;//len
        ptr += 4;//type
        ptr += len;//data
        ptr += 4;//crc

    }
    
    printf("PNG file size: %d", ptr - start + 12);
    
    return 0;
}