#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#define actions_to_die 20
int gold;
pthread_mutex_t g_mutex;
void *miner(void *id)
{
    for (int i = 0; i < actions_to_die; i++)
    {
        pthread_mutex_lock(&g_mutex);
        gold += 10;
        printf("Miner %d gathered 10 gold\n", id + 1);
        pthread_mutex_unlock(&g_mutex);
        sleep(2);
    }
    return 0;
}
void *trader(void *id)
{
    for (int i = 0; i < actions_to_die; i++)
    {
        pthread_mutex_lock(&g_mutex);
        if (gold < 10)
            printf("The warehouse is empty, cannot sell!\n", id + 1);
        else
        {
            printf("Trader %d sold 10 gold\n", id + 1);
            gold -= 10;
        }
        pthread_mutex_unlock(&g_mutex);
        sleep(2);
    }
    return 0;
}

int main(int argc, char *argv[])
{
    pthread_mutex_init(&g_mutex, NULL);
    int miners = 1;
    int traders = 1;
    if (argc == 3)
    {
        miners = atoi(argv[1]);
        traders = atoi(argv[2]);
    }
    pthread_t threads[miners + traders];
    int thr_ind = 0;
    for (int i = 0; i < miners; i++)
    {
        pthread_create(threads + thr_ind++, NULL, &miner, i);
    }

    for (int i = 0; i < traders; i++)
    {
        pthread_create(threads + thr_ind++, NULL, &trader, i);
    }

    for (int i = 0; i < thr_ind; i++)
    {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&g_mutex);
    printf("Gold: %d\n", gold);
}