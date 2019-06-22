#include <stdio.h>
#include "gen.h"

int main()
{
    int array[8192];
    for (int i = 0; i < 8192; i++)
    {
        array[i] = 39;
    }

    generate(array, 641794);

    for (int i = 0; i < 8192; i++)
    {
        printf("%d - %d\n", i, array[i]);
    }

    printf("verify - %ld", verify(array));
}