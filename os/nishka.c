#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 3

void *hello(void *idd)
{
    int id = (int)idd;
    printf("Hello from world");
    return NULL;
}
int main()
{
    pthread_t thread[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&thread[i], NULL, hello, (void *)i);

        return 0;
    }
}
