#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // setting up
    string name = GetString();
    int length = strlen(name);
    
    // printing the initials
    if (isalpha(name[0]))
    {
    printf("%c", toupper(name[0]));
    }
    
    // loop
    for (int i = 1; i < length; i++)
    {
        if (name[i-1] == ' ' && isalpha(name[i]))
        {
            printf("%c", toupper(name[i]));
        }
    }
    printf("\n");
}
