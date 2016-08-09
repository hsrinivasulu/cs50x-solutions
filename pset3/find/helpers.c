/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

int midPoint (int a, int b);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (n<0)
    {
        return false;
    }
    
    // variables and loop for binary search
    int max = n-1, min = 0;
    
    while (max >= min)
    {
        int current = midPoint(max,min);
        
        if (values[current] > value)
        {
            max = current - 1;
        }
        else if (values[current] < value)
        {
            min = current + 1;
        }
        else
        {
            return true;
        }
    }   
    return false;
}

int midPoint (int a, int b)
{
    if ((a+b)%2 == 0)
    {
        return (a+b)/2;
    }
    else
    {
        return ((a+b)/2);
    }
}


/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{   

    // main sorting loop
    for (int i = 0; i < n; i++)
    {   
        // default values for minVal and minIndice
        int minVal = values[i], minIndice = i;
        
        //figuring out smallest value in a run
        for (int j = i; j < n; j++)
        {
            if (values[j] < minVal)
            {
                minVal = values[j];
                minIndice = j;
            }
        }        
        
        //putting ordered value in correct position by swapping
        int swap = values[i];
        values[i] = minVal;
        values[minIndice] = swap;
    }
}
