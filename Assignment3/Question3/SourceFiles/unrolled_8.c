/* Author: Caitlin Coulombe, T00756521
 * Date: July 6, 2024
 * Course: COMP 2131
 * Assignment 3: Write a C function to pass two numbers to the function and calculate the sum of all the numbers between them (both inclusive)
 *      * version with for loop
 */

// import headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 50

//-------------------------------------------------------------------------------------------------------------------
// main() takes user input to determine what action to take and acts accordingly
//-------------------------------------------------------------------------------------------------------------------
int main(int argc, char const *argv[])
{
    // variables
    int array[SIZE];
    int total = 0;

    // initialize each value in the array
    for(int i = 0; i < SIZE; i++)
    {
        array[i] = i + 1;
    }

    clock_t start, end;
    double cpu_time_used;

    // Measure time for the unrolled loop
    start = clock();
    // sum the array - this is the array that needs to be unrolled
    int i = 0;
    for(; i < SIZE - 8; i += 8)
    {
        total += array[i];
        total += array[i + 1];
        total += array[i + 2];
        total += array[i + 3];
        total += array[i + 4];
        total += array[i + 5];
        total += array[i + 6];
        total += array[i + 7];
    }   

    // handle the remaining elements in the array
    for(; i < SIZE; i++)
    {
        total += array[i];
    }
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Unrolled loop time: %f seconds\n", cpu_time_used);

    printf("The total is: %d\n", total);
    return 0;
}
