#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char name[20], i;
    printf("What is your name? ");
    scanf("%s", name);
    printf("Hello %s.\n", name);

    // determine the length of the name
    for(i = 0; name[i] !='\0'; ++i);
    printf("Your name is %d letters long.\n", i);
    return 0;
}