/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"
#include <stdio.h>
#include <string.h>
/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
   
    // TODO: implement a searching algorithm
    if( n<= 0 )
      return false;
    else
    {
        int min = 0, max = n-1, mid = 0;
        while(min<=max)
        {
         mid =  (min + max)/2;
         if(values[mid] == value)
                  return true;
        else
        {
            if(value < values[mid])
            {
                max = mid-1; 
            }
            else if( value > values[mid])
            {
                min = mid+1;
            }

        }
        }
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    if(n<=0)
    {
        return;
    }
    int limit=values[0];
    for(int i=1; i<n ; i++)
    {
        if(limit< values[i])
             limit = values[i];           // finding the biggest value i-e, RANGE/LIMIT in array
    }
    // TODO: implement a sorting algorithm
    int count[limit+1];
    int sortArray[n];                     // carries sorted values
    memset(count, 0, sizeof(count));             // initializing count array with zeros
    for(int i=0; i<n; i++)
    {
        count[values[i]]++;                    // adding count of element
    }
    
    for(int i=1; i<=limit; i++)
    {
        count[i] += count[i-1];                  // adding previous counts to immediate one
    }
    for(int i=0; i< n; i++)
    {
        sortArray[count[values[i]]-1]= values[i];       // placing elements at corresponding positions indicated by count array
        count[values[i]]--;
    }
    printf("Sorted array is:");
       
    for(int i=0; i< n; i++)
    {
         printf("%i %c", sortArray[i],' ');
    }
    return;
}

void sort1(int *values, int n)
{
    if(n<=0)
    {
        printf("array is empty!");
        return;
    }
    // TODO: implement a sorting algorithm
    int limit=values[0];
    for(int i=1; i<n ; i++)
    {
        if(limit< values[i])
             limit = values[i];           // finding the biggest value i-e, RANGE/LIMIT in array
    }
    int count[limit+1];
    int sortArray[n];                     // carries sorted values
    memset(count, 0, sizeof(count));             // initializing count array with zeros
    for(int i=0; i<n; i++)
    {
        count[values[i]]++;                    // adding count of element
    }
    
    for(int i=1; i<=limit; i++)
    {
        count[i] += count[i-1];                  // adding previous counts to immediate one
    }
    for(int i=0; i< n; i++)
    {
        sortArray[count[values[i]]-1]= values[i];       // placing elements at corresponding positions indicated by count array
        count[values[i]]--;
    }

    for(int i=0; i< n; i++)
    {
        values[i] = sortArray[i]; 
    }
    return ;
}
