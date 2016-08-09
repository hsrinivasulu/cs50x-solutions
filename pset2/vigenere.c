#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Please enter one argument.\n");
        return 1;
    }
    else
    {
        string key = argv[1];
        int keyl = strlen(key);
        
        // checking whether the key corresponds to requirements
        for (int i = 0; i < keyl; i++)
        {
            if (!(isalpha(key[i])))
            {
                printf("Key must be alphabetic.\n");
                return 1;
            }
        }
        
        // assuming it passes the test, let's get on with work
        string s = GetString();
        int l = strlen(s), dkey[l];
        
        // generating a duplicate key
        for (int i = 0, nl = 0; i < l; i++)
        {
            if (isalpha(s[i]))
            {
                dkey[i] = toupper(key[nl % keyl]) - 'A' ;
                nl++;
            }
        }
        
        // debug, printing out the duplicate key
        /*
        for (int i = 0; i < l; i++)
        {
            if (isalpha(s[i]))
            {
                printf("%d", dkey[i]);
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
        */
        
        // applying the key
        
        for (int i = 0; i < l; i++)
        {
            if (isupper(s[i]))
            {
                s[i] = ((s[i] - 'A' + dkey[i]) % 26) + 'A';
            }
            else if (islower(s[i]))
            {
                s[i] = ((s[i] - 'a' + dkey[i]) % 26) + 'a';
            }
        }
        printf("%s\n",s);
    }
}
