#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 0 || n > 23);
    int i;
    for (i = 0; i < n; i++)
    {
        int j;
        for (j = 0; j < n - 1 - i; j++)
        {
            printf(" ");
        }
        for (j = 0; j < 2 + i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
    return 0;
}