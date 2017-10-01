/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // TODO: comment me        // in case of wrong command line arguments, outputs clears how to use function
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // TODO: comment me      // 1st argument(how many values user wants to generate randomly) is stored in integer n
    int n = atoi(argv[1]);

    // TODO: comment me     // if number of arguments are 3 i-e, seed is provided along with n then generate seed of provided value 
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else                      // if seed is not provided then seed with value of time(NULL)
    {
        srand48((long) time(NULL));
    }

    // TODO: comment me          // printing randomly generated values upto desired 'n'
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
