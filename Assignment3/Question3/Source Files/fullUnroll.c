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
    total += array[0];
    total += array[1];
    total += array[2];
    total += array[3];
    total += array[4];
    total += array[5];
    total += array[6];
    total += array[7];
    total += array[8];
    total += array[9];
    total += array[10];
    total += array[11];
    total += array[12];
    total += array[13];
    total += array[14];
    total += array[15];
    total += array[16];
    total += array[17];
    total += array[18];
    total += array[19];
    total += array[20];
    total += array[21];
    total += array[22];
    total += array[23];
    total += array[24];
    total += array[25];
    total += array[26];
    total += array[27];
    total += array[28];
    total += array[29];
    total += array[30];
    total += array[31];
    total += array[32];
    total += array[33];
    total += array[34];
    total += array[35];
    total += array[36];
    total += array[37];
    total += array[38];
    total += array[39];
    total += array[40];
    total += array[41];
    total += array[42];
    total += array[43];
    total += array[44];
    total += array[45];
    total += array[46];
    total += array[47];
    total += array[48];
    total += array[49];


    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Unrolled loop time: %f seconds\n", cpu_time_used);

    printf("The total is: %d\n", total);
    return 0;
}
