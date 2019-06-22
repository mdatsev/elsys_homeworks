#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define nRacers 20
#define nCars 5

pthread_t racers[nRacers];
pthread_mutex_t cars[nCars];

void *racer(void *id)
{
    int driven[nCars] = {0};
    unsigned int car = 0;
    while (1)
    {
        car++;
        car %= nCars;
        int allDriven = 1;
        for (int i = 0; i < nCars; i++)
            if (!driven[i])
                allDriven = 0;
        if (allDriven)
            break;
        if (driven[car])
        {
            continue;
        }
        if (pthread_mutex_trylock(cars + car))
        {

            continue;
        }
        printf("Buyer %d takes car %d.\n", id, car);
        sleep(1);
        printf("Buyer %d returns car %d.\n", id, car);
        driven[car] = 1;
        pthread_mutex_unlock(cars + car);
    }
}

int main()
{
    for (int i = 0; i < nCars; i++)
    {
        pthread_mutex_init(cars + i, NULL);
    }
    for (int i = 0; i < nRacers; i++)
    {
        pthread_create(racers + i, NULL, racer, (void *restrict)i);
    }
    for (int i = 0; i < nRacers; i++)
    {
        pthread_join(racers[i], NULL);
    }
    for (int i = 0; i < nCars; i++)
    {
        pthread_mutex_destroy(cars + i);
    }
    return 0;
}