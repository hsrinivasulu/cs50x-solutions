#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <cs50.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Please enter one argument. \n");
        return 1;
    }
    else
    {
        printf("%s\n", crypt(argv[1], "50"));
    }
}
