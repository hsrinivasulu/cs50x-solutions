#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{
    // getting things in order
    if (argc > 1)
    {
        // initialising strings and limits
        int k = atoi(argv[1]);
        string s = GetString();
        int length = strlen(s);
        
        // printing encrypted version
        for (int i = 0; i < length ; i++)
        {
            if (s[i] >= 'a' && s[i] <= 'z')
            {
                s[i] = ((s[i] - 'a' + k) % 26) + 'a';
            }
            else if (s[i] >= 'A' && s[i] <= 'Z')
            {
                s[i] = ((s[i] - 'A' + k) % 26) + 'A';
            }
        }
        printf("%s\n", s);
        return 0;
    }
    else
    {
        // handling improper output
        printf("Please enter a key next time\n");
        return 1;
    }
}
