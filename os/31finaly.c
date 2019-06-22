#include <pthread.h>
#include <stdio.h>
#include <math.h>
#define NUM_THR 2
#define ARRAY_SIZE 10000

double total;

void *sum(void *mutex)
{
    pthread_mutex_t *m = (pthread_mutex_t *)mutex;

    int i;
    for (int i = 0; i < ARRAY_SIZE / NUM_THR; i++)
    {
        double calc = sin(i) * sin(i) + cos(i) * cos(i);
        pthread_mutex_lock(m);
        total += calc;
        pthread_mutex_unlock(m);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    pthread_t threads[NUM_THR];
    for (int i = 0; i < NUM_THR; i++)
    {
        pthread_create(threads + i, NULL, &sum, &mutex);
    }
    for (int i = 0; i < NUM_THR; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("Sum: %f", total);
}