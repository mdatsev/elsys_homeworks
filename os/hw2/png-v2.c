#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <arpa/inet.h>

void *read_image(const char *filepath);

int main(int argc, char **argv)
{
    uint32_t dataLen;
    int8_t *start = (int8_t *)read_image(argv[1]);
    int8_t *currentPointer = start;
    if (currentPointer)
    {
        if (!strncmp((const char *)currentPointer, "\x89\x50\x4E\x47\x0D\x0A\x1A\x0A", 8))
        {
            currentPointer += 8;
            while (1)
            {
                if (!strncmp((const char *)(currentPointer + 4), "\x49\x45\x4E\x44", 4))
                {
                    break;
                }
                dataLen = ntohl(*(uint32_t *)currentPointer);
                ///Whole data length and type
                currentPointer += 8;
                currentPointer += dataLen;
                ///CRC stuff
                currentPointer += 4;
            }
            ///plus the starting signature and IEND crc
            printf("PNG image width: %d\n", ntohl(*(uint32_t *)(start + 16)));
            printf("PNG image height: %d\n", ntohl(*(uint32_t *)(start + 20)));
            printf("PNG file size: %d", currentPointer - start + 12);
            return 0;
        }
        else
        {
            printf("Unable to parse file");
            return -2;
        }
    }
    else
    {
        printf("Unable to open file");
        return -1;
    }
}