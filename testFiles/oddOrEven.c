#include <stdio.h>

int main(void)
{
    int number;
    printf("Please enter a number ");
    scanf("%d", number);

    if(number & 1)
    {
        printf("The entered number is odd");
    }
    else
    {
        printf("The entered number is even");
    }

}