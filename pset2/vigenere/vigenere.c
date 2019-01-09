#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void encode(char* n, char *t);

int main(int argc, char* argv[])
{
    if (argc == 2)
    {
        for (int i = 0; argv[1][i] != '\0'; i++) if (!isalpha(argv[1][i])) return 1;
        string text = get_string("plaintext: ");
        encode(argv[1], text);
        printf("ciphertext: %s\n", text);
        return 0;
    }
    else return 1;
}

void encode(char* n, char *t)
{
    int len = strlen(n);
    int i = 0, k = 0;
    while (t[i] != '\0')
    {
        if (isupper(t[i]))
        {
            if (isupper(n[k % len]))
            {
                t[i] -= 'A';
                t[i] = (t[i] + (n[k++ % len] - 'A')) % 26;
                t[i] += 'A';
            }
            else if (islower(n[k % len]))
            {
                t[i] -= 'A';
                t[i] = (t[i] + (n[k++ % len] - 'a')) % 26;
                t[i] += 'A';
            }
        }
        else if (islower(t[i]))
        {
            if (isupper(n[k % len]))
            {
                t[i] -= 'a';
                t[i] = (t[i] + (n[k++ % len] - 'A')) % 26;
                t[i] += 'a';
            }
            else if (islower(n[k % len]))
            {
                t[i] -= 'a';
                t[i] = (t[i] + (n[k++ % len] - 'a')) % 26;
                t[i] += 'a';
            }
        }
        i++;
    }
}