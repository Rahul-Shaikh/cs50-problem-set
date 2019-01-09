#include <stdio.h>
#include <cs50.h>
#include <math.h>
int main(void)
{
    double cash;
    do
    {
        cash = get_float("Change owed: ");
    }
    while (cash < 0);
    cash = cash * 100;
    int change = (int) round(cash);
    int count = 0;
    count += change / 25;
    change %= 25;
    count += change / 10;
    change %= 10;
    count += change / 5;
    change %= 5;
    count += change;
    printf("%d\n", count);
    return 0;
}