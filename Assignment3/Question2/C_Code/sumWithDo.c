/* Author: Caitlin Coulombe, T00756521
 * Date: July 6, 2024
 * Course: COMP 2131
 * Assignment 3: Write a C function to pass two numbers to the function and calculate the sum of all the numbers between them (both inclusive)
 *      * version with while loop
 */

// import headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int sumArguments(int num1, int num2);

//-------------------------------------------------------------------------------------------------------------------
// main() takes user input to determine what action to take and acts accordingly
//-------------------------------------------------------------------------------------------------------------------
int main(int argc, char const *argv[])
{
    // variables
    int num1 = 5;
    int num2 = 10;

    int total = sumArguments(num1, num2);

    printf("The sum of all the numbers between %d and %d, inclusive, is %d\n", num1, num2, total);

}

//-------------------------------------------------------------------------------------------------------------------
// sumArguments() sums all of the numbers between the two parameters, inclusive
//-------------------------------------------------------------------------------------------------------------------
int sumArguments(int num1, int num2)
{
    // variabes
    int total = 0;

    do
    {
        total += num1;
        num1++;
    } while (num1 <= num2);
    

    return total;
}
