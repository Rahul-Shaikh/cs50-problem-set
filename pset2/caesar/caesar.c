#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>

void encode(int n, char *t);

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        long n;
        n = strtol(argv[1], NULL, 10);
        string text = get_string("plaintext: ");
        encode(n,text);
        printf("ciphertext: %s\n", text);
        return 0;
    }
    else return 1;
}

void encode(int n, char *t)
{
    int i = 0;
    while (t[i] != '\0')
    {
        if (isupper(t[i]))
        {
            t[i] -= 'A';
            t[i] = (t[i] + n) % 26;
            t[i] += 'A';
        }
        else if (islower(t[i]))
        {
            t[i] -= 'a';
            t[i] = (t[i] + n) % 26;
            t[i] += 'a';
        }
        i++;
    }
}