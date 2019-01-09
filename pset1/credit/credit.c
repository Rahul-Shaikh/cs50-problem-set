#include <stdio.h>
#include <cs50.h>
#include <string.h>

int even_calc(int x);
int odd_calc(int x);
long long int reverse(long long int n);

int main(void)
{
    long long int credit_number;
    char *temp = malloc(sizeof(char)*18);
    do
    {
    credit_number = get_long_long("Number: ");
    }
    while (credit_number < 0);
    sprintf(temp, "%lld", credit_number);
    int sum = 0, count = 1;
    while (credit_number != 0)
    {
        if (count % 2 == 1) sum += odd_calc(credit_number % 10);
        else sum += even_calc(credit_number % 10);
        credit_number /= 10;
        count++;
    }
    if (sum % 10 == 0)
    {
        if ((temp[0] == '3') && ((temp[1] == '4') || (temp[1] == '7')) && (strlen(temp) == 15)) printf("AMEX\n");
        if ((temp[0] == '4') && ((strlen(temp) == 13) || (strlen(temp) == 16))) printf("VISA\n");
        if ((temp[0] = '5') &&((temp[1] == '1') || (temp[1] == '2') || (temp[1] == '3') || (temp[1] == '4') || (temp[1] == '5')) && (strlen(temp) == 16)) printf("MASTERCARD\n");
        else printf("INVALID\n");
    }
    else printf("INVALID\n");
    return 0;
}

int even_calc(int x)
{
    x *= 2;
    int sum = 0;
    while (x != 0)
    {
        sum += (x % 10);
        x /= 10;
    }
    return sum;
}

int odd_calc(int x)
{
    return x;
}