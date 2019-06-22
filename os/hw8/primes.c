//------------------------------------------------------------------------
// NAME: Martin Datsev
// CLASS: XIb
// NUMBER: 17
// PROBLEM: #3
// FILE NAME: primes.c
// FILE PURPOSE:
// reads commands from stdin and counts primes
// p N - count primes up to N
// e - exit
//------------------------------------------------------------------------

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

//------------------------------------------------------------------------
// FUNCTION: is_prime
// returns if a number is prime
// PARAMETERS:
// n - the number
//------------------------------------------------------------------------

bool is_prime(unsigned int n)
{
    for (int j = 2; j < n; j++)
    {
        if (n % j == 0)
            return false;
    }
    return true;
}

//------------------------------------------------------------------------
// FUNCTION: count_primes
// counts the number of primes up to n
// PARAMETERS:
// n_vp - the number (value passed as void*) (to fit create_thread start_routine param)
//------------------------------------------------------------------------

void *count_primes(void *n_vp)
{
    unsigned int n = (unsigned int)n_vp;
    unsigned int count = 0;
    for (int i = 2; i < n; i++)
    {
        if (is_prime(i))
            count++;
    }
    printf("Number of primes for N=%d is %d\n", n, count);
}

//------------------------------------------------------------------------
// FUNCTION: main
// reads commands from stdin and creates threads to count primes
//------------------------------------------------------------------------
int main()
{
    char *line = NULL;
    size_t len = 0;
    while (1)
    {
        ssize_t read = getline(&line, &len, stdin);
        if (line[0] == 'e')
        {
            pthread_exit(NULL);
        }
        else if (line[0] == 'p')
        {
            unsigned int N = atoi(line + 2);
            pthread_t thrid;
            pthread_create(&thrid, NULL, &count_primes, (void *)N);
            printf("Prime calculation started for N=%d\n", N);
        }
        else
        {
            printf("Supported commands:\np N - Starts a new calculation for the number of primes from 1 to N\ne - Waits for all calculations to finish and exits\n");
        }
    }
    return 0;
}

//