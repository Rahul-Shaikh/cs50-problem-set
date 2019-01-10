#include <stdio.h>
#include <string.h>
#define _GNU_SOURCE
#include <crypt.h>
#define rep(i,n) for (int i = 0; i < n; i++)
void crack(char* pass, char *hash);

int main(int argc, char* argv[])
{
    char pass[6];
    if (argc == 2)
    {
        crack(pass, argv[1]);
        printf("%s\n", pass);
        return 0;
    }
    else
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }
}

void crack(char* pass, char *hash)
{
    char salt[3];
    memcpy(salt, hash, 2);
    //brute force
    int flag = 0;
    char all[] = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    rep(i1, 53)
    {
        rep(i2, 53)
        {
            rep(i3, 53)
            {
                rep(i4, 53)
                {
                    for (int i5 = 1; i5 < 53; i5++)
                    {
                        pass[0] = all[i5];
                        pass[1] = all[i4];
                        pass[2] = all[i3];
                        pass[3] = all[i2];
                        pass[4] = all[i1];
                        if (!strcmp(hash, crypt(pass, salt)))
                        {
                            flag = 1;
                            break;
                        }
                    }
                    if (flag) break;
                }
                if (flag) break;
            }
            if (flag) break;
        }
        if (flag) break;
    }
}