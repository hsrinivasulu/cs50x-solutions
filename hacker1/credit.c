#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // credit.c ~hsrinivasulu
    long long number, input;
    int sum1 = 0, sum2 = 0, i = 0;
    
    printf("Please enter your credit card's number: ");
    input = GetLongLong();
    number = input;
    
    // figuring out number length and checksums
    for (i = 0; number != 0; i++)
    {
        if (i % 2 == 0)
            sum1 += (number % 10);
        else 
            sum2 += ((2 * (number % 10)) % 10) + (((2 * (number % 10)) - ((2 * (number % 10)) % 10)) / 10);
        number /= 10;
    }
    
    //checking validity, and if valid, card type
    number = input;
    // printf("%d + %d = %d\n", sum1, sum2, sum1+sum2);
    if ((sum1 + sum2) % 10 != 0)
        printf("INVALID\n");
    else
    {
        switch (i)
        {
            case 13:
                if ((int) (number / pow(10, 12)) == 4)
                    printf("VISA\n");
                else
                    printf("INVALID\n");
                break;
                
            case 15:
                if ((int) (number / pow(10, 13)) == 34 || (int) (number / pow(10, 13)) == 37)
                    printf("AMEX\n");
                else
                    printf("INVALID\n");
                break;
                
            case 16:
                if ((int) (number / pow(10, 15)) == 4)
                    printf("VISA\n");
                else 
                {
                    switch ((int) (number / pow(10, 14)))
                    {
                        case 51:
                        case 52:
                        case 53:
                        case 54:
                        case 55:
                            printf("MASTERCARD\n");
                            break;
                        default:
                            printf("INVALID\n");
                    }
                }
                break;
            
            default:
                printf("INVALID\n");
        }
    }
}
