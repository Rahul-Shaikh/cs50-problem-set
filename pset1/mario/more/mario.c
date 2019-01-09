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
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
        for (int j = 0; j < 1 + i; j++)
        {
            printf("#");
        }
        printf(" ");
        printf(" ");
        for (int j = 0; j < 1 + i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}