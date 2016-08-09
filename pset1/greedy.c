#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    while (1)
    {
        float input;
        int cents, count;
        printf("How much change?\n");
        input = GetFloat();
        cents = round(input * 100);
        // directly getting the number of cents
        count = 0;
        if (cents >= 0)
        // sanity check
        {
            // figuring out number of 25, 10, 5, and 1 cent coins
            while (cents >= 25)
            {
                cents -= 25;
                count++;
            }
            while (cents >= 10)
            {
                cents -= 10;
                count++;
            }
            while (cents >= 5)
            {
                cents -= 5;
                count++;
            }
            while (cents >= 1)
            {
                cents -= 1;
                count++;
            }
            // spitting out the number
            printf("%d\n", count);
            // "Here, we hit it, and quit it."
            break;
        }
    }
}
