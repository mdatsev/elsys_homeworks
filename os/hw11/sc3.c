//--------------------------------------------
// NAME: Martin Datsev
// CLASS: Xib
// NUMBER: 17
// PROBLEM: #3
// FILE NAME: sc3.c (unix file name)
// FILE PURPOSE:
// Implements starcraft 3 minigame
// You can input commands to train SCVs that mine from mineral blocks (reffered to as
// mines in this program because it's shorter) and marines. Train
// 20 marines to win. You can specif number of mineral blocks as argument
//---------------------------------------------

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>
#include <errno.h>

//#define sleep(_)
#define startingMinerals 500 /* initial minerals per mine */
int nMines = 2;              /* default initial mines */
int nSCVs = 5;               /* initial SCVs */
int nMarines = 0;            /* initial marines */

void init_game();
void interpret_commands();

//--------------------------------------------
// FUNCTION: main
// deals with the cmd line arguments for the minerals
// calls the game setup and starts the interpreter
// PARAMETERS:
// argc - number of arguments
// argv - their values
//----------------------------------------------
int main(int argc, char *argv[])
{
    if (argc == 2)              /* if an argument is supplied */
        nMines = atoi(argv[1]); /* change the number of mines to the arg. */
    init_game();                /* setup the game */
    interpret_commands();       /* start the command interpreter */
}

// STRUCT: mineral_container_t
// holds mineral value and a mutex for that value
typedef struct
{
    pthread_mutex_t mutex; /* lock this mutex while modifying the minerals */
    int minerals;
} mineral_container_t;

mineral_container_t *mines;
mineral_container_t command_center;
pthread_t scvs[200];

pthread_t start_thread_checked(void *(*function)(void *), long param);
void lock_mutex_checked(pthread_mutex_t *mutex);
void unlock_mutex_checked(pthread_mutex_t *mutex);

void *scv(void *id);

//--------------------------------------------
// FUNCTION: init_game
// initializes all the initial units and mines
// allocating memory and starting up threads
//----------------------------------------------
void init_game()
{
    mines = malloc(nMines * sizeof(mineral_container_t)); /* allocate mines */
    for (int i = 0; i < nMines; i++)                      /* then initialize: */
    {
        if (pthread_mutex_init(&mines[i].mutex, NULL))    /* the internal mutex */
        {
            perror("Failed to initialize mutex");
            exit(1);
        }
        mines[i].minerals = startingMinerals;             /* and the starting minerals */
    }
    for (int i = 0; i < nSCVs; i++) /* for each initial SCV */
    {                               /* start an SCV thread */
        scvs[i] = start_thread_checked(scv, i);
    }
}

void train_unit(int time, int cost, int *total, const char *message);
void end_game();

void safe_printf(const char *format, ...);

//--------------------------------------------
// FUNCTION: interpret_commands
// takes commands and interprets them
//----------------------------------------------
void interpret_commands()
{
    while (1)
    {
        int command = getchar();
        if (command == 'm')
        { /* m - train marine */
            train_unit(1, 50, &nMarines, "You wanna piece of me, boy?\n");
            if (nMarines == 20) /* if game won */
                end_game();     /* go to end game */
        }
        else if (command == 's')
        { /* s - train SCV */
            train_unit(4, 50, &nSCVs, "SCV good to go, sir.\n");
            scvs[nSCVs - 1] = start_thread_checked(scv, nSCVs - 1); /* start a thread for it */
        }
    }
}

bool add_minerals(mineral_container_t *container, int amount);

//--------------------------------------------
// FUNCTION: end_game
// cleanup - destroyuing mutexes, joining threads
// prints the ending message
// exits the program
//----------------------------------------------
void end_game()
{
    for (int i = 0; i < nSCVs; i++)
    { /* wait for all SCVs to finish */
        if (pthread_join(scvs[i], NULL))
        {
            perror("Failed to join thread");
            exit(2);
        }
    }
    for (int i = 0; i < nMines; i++)
    { /* destroy all the mine mutexes */
        if (pthread_mutex_destroy(&mines[i].mutex))
        {
            perror("Failed to destroy mutex");
        }
    }
    safe_printf("Map minerals %d, player minerals %d, SCVs %d, Marines %d\n",
                nMines * startingMinerals, command_center.minerals, nSCVs, nMarines);
    free(mines);
    exit(0);
}

bool all(bool arr[], size_t size);

//--------------------------------------------
// FUNCTION: scv
// thread function for an SCV
// collects minerals from the mines and transports them to the command center
// PARAMETERS:
// id - int(!) value, the SCV id
//----------------------------------------------
void *scv(void *id)
{
    long scv_number = (long)id + 1;                /* to the numbering from 1 */
    bool empty_mines[nMines];                      /* to locally track the empty mines */
    memset(empty_mines, 0, nMines * sizeof(bool)); /* set all are not empty (0) */
    for (int i = 0; !all(empty_mines, nMines); i++, i %= nMines)
    { /* try new mine while not all are empty */
        if (empty_mines[i])
            continue; /*skip if block is marked empty locally */
        /* Action 1: Moving to empty block */
        sleep(3); 
        /* Action 2: Check if block is free */
	    int lock = pthread_mutex_trylock(&mines[i].mutex);
        if (lock == EBUSY)
            continue; /* skip if block is taken */
        else if(lock != 0)
        {
            perror("trylock error");
            exit(3);
        }
        if (mines[i].minerals == 0)
        { /* if block is found to be empty (someone else mined it in the meantime) */
            empty_mines[i] = true; /* mark as empty and */
            unlock_mutex_checked(&mines[i].mutex);
            continue;              /* skip it */
        }

        safe_printf("SCV %d is mining from mineral block %d\n", scv_number, i + 1);
        int capacity = 8; /* max SCV capacity */
        if (mines[i].minerals < capacity)
            /* if fewer minerals pretend they are the capacity (to take all of them but not more)*/
            capacity = mines[i].minerals;
        /* Action 3: dig minerals */
        mines[i].minerals -= capacity; /* subtract them from the mine */
        unlock_mutex_checked(&mines[i].mutex);
        safe_printf("SCV %d is transporting minerals\n", scv_number);
        /* Action 4: transport to Command center */
        sleep(2);
        /* Action 5: dump the minerals to the Command center */
        add_minerals(&command_center, capacity);
        safe_printf("SCV %d delivered minerals to the Command center\n", scv_number);
    }   /* Action 6: (Go to step 1) */
    return 0;
}

//--------------------------------------------
// FUNCTION: train_unit
// simulates training a unit
// PARAMETERS:
// time - time in seconds to train
// cost - cost to train
// total - value to update after training
// message - message to print after succesful training
//----------------------------------------------
void train_unit(int time, int cost, int *total, const char *message)
{
    /* subtract the cost (reuse add with negative sign) */
    if (add_minerals(&command_center, -cost))
    { /* if they can be subtacted (enough money) */
        sleep(time);          /* simulate the training time */
        safe_printf(message); /* print the training message */
        (*total)++;           /* increase the total units */
    }
}

//--------------------------------------------
// FUNCTION: add_minerals
// adds minerals to a mineral_container_t
// supports negative values to subtract and checks if minerals are enough
// prints "Not enough minerals.\n" if not enough
// RETURN: true if operation was succesful, else false
// PARAMETERS:
// container - container to add to
// amount - amount to add
//----------------------------------------------
bool add_minerals(mineral_container_t *container, int amount)
{
    lock_mutex_checked(&container->mutex);
    if (container->minerals + amount >= 0) /* check if enough money */
    {
        container->minerals += amount;     /* add the amount */
        unlock_mutex_checked(&container->mutex);
        return true; /* return succesful transaction */
    }
    /* else not enough minerals */
    safe_printf("Not enough minerals.\n");
    unlock_mutex_checked(&container->mutex);
    return false; /* return unsuccesful */
}

//--------------------------------------------
// FUNCTION: add_minerals
// utility function to check if all values of an array are truthy
// PARAMETERS:
// arr - array to check
// size - size of the array
//----------------------------------------------
bool all(bool arr[], size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (!arr[i]) /* if any is false return false */
            return false;
    }
    return true;     /* else return true */
}

//--------------------------------------------
// FUNCTION: safe_printf
// thread safe printf wrapper
// PARAMETERS: same as printf - see `man printf`
//----------------------------------------------
void safe_printf(const char *format, ...)
{
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    va_list valist;
    va_start(valist, format);
    lock_mutex_checked(&mutex);
    vprintf(format, valist);
    unlock_mutex_checked(&mutex);
    va_end(valist);
}

//--------------------------------------------
// FUNCTION: start_thread_checked
// error checked and simple pthread_create wrapper
// RETURN: the new thread id
// PARAMETERS:
// function - function to invoke in the new thread
// param - parameter passed to 'function'
//----------------------------------------------
pthread_t start_thread_checked(void *(*function)(void *), long param)
{
    pthread_t id;
    if (pthread_create(&id, NULL, function, (void *)param))
    {
        perror("Failed to create a thread");
        exit(-1);
    }
    return id;
}

//--------------------------------------------
// FUNCTION: lock_mutex_checked
// error checked pthread_mutex_lock wrapper
// PARAMETERS:
// mutex - mutex to lock
//----------------------------------------------
void lock_mutex_checked(pthread_mutex_t *mutex)
{
    if (pthread_mutex_lock(mutex))
    {
        perror("Failed to lock mutex");
        exit(-2);
    }
}

//--------------------------------------------
// FUNCTION: unlock_mutex_checked
// error checked pthread_mutex_unlock wrapper
// PARAMETERS:
// mutex - mutex to unlock
//----------------------------------------------
void unlock_mutex_checked(pthread_mutex_t *mutex)
{
    if (pthread_mutex_unlock(mutex))
    {
        perror("Failed to unlock mutex");
        exit(-3);
    }
}


