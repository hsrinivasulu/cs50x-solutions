#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height, i, j;
    while (1) 
    // loop to ensure that the user is given a chance to enter a valid value
    {
        printf("Height: ");
        height = GetInt();
        if (height >= 0 && height <= 23) 
        // loop entry check
        {
            for (i = 0; i < height; i++) 
            // regulates number of lines
            {   
                for (j = height - (i + 1); j > 0; j--) 
                // regulates number of spaces
                {
                    printf(" ");
                }
                printf("#"); 
                // in order to make below code more intuitive
                for (j = i; j > 0; j--) 
                // prints the 'bricks'
                {
                    printf("#");
                }
                // repeating the process for the double pyramid
                printf("  #");
                for (j = i; j > 0; j--) 
                // prints the 'bricks'
                {
                    printf("#");
                }
                /* for (j = height - (i + 1); j > 0; j--) 
                // regulates number of spaces
                {
                    printf(" ");
                } */
                
                // newline
                printf("\n");
            }
            return 0;
            break; 
            // to quit the loop once the output has been printed
        }
    }
}
