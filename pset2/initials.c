#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    int i = 1;
    string name = GetString();
    
    // simply print first letter, if it is infact a letter
    
    if ((name[0] >= 'a' && name[0] <= 'z') || (name[0] >= 'A' && name[0] <= 'Z'))
    {
        printf("%c", toupper(name[0]));
    }

    // parsing
    do
    {
        if (name[i - 1] == ' ')
        {
            printf("%c", toupper(name[i]));
        }
        i++;
    } while (name[i] != '\0');
    
    // for that extra newline
    printf("\n");
}
