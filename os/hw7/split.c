#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <sys/types.h>
#include <unistd.h>

char **split(const char *line, char delimiter, int *size)
{
    const char *start = line;
    for (int i = 0; line[i] == delimiter; i++)
    {
        start = &line[i + 1];
    }
    char *mutable = malloc((strlen(start) + 1) * sizeof(char));
    strcpy(mutable, start);
    char **result = NULL;
    int argc = 0;
    char *beginning = &mutable[0];
    for (char *cur = &mutable[0];; cur++)
    {
        if (*cur == delimiter || *cur == '\0')
        {
            if (cur - beginning == 0)
            {
                beginning = cur + 1;
                if (*cur == '\0')
                    break;
                else
                    continue;
            }
            argc++;

            result = realloc(result, (argc + 1) * sizeof(char *));
            result[argc - 1] = beginning;
            beginning = cur + 1;
            if (*cur == '\0')
                break;
            *cur = '\0';
        }
    }

    result[argc] = NULL;
    if (size)
    {
        *size = argc;
    }
    return result;
}

int main()
{
    const char *test = "hello   world 1  22 333  4444";
    int size;
    char **result = split(test, ' ', &size);
    for (int i = 0; i < size; i++)
    {
        printf("`%s`\n", result[i]);
    }
    free(result[0]);
    free(result);
}