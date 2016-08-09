#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

int main(int argc, char* argv[])
{
    //initialise variables
    FILE *new = NULL, *card = fopen("card.raw", "r");
    int num = 0;
    uint8_t *data = malloc(sizeof(uint8_t) * 512);
    
    while (!feof(card))
    {
        // read block of card.raw and check whether it is the leading block of a .jpg along with some fuckery
        int i;
        for (i = 0; i < sizeof(data); i++)
        {
            fread(&data[i], sizeof(uint8_t), 1, card);
            if (feof(card))
            {
                break;
            }
        }
        
        if (i != sizeof(data))
        {
            fclose(new);
            break;
        }
        
        if (data[0] == (uint8_t) 0xff && data[1] == (uint8_t) 0xd8 && data[2] == (uint8_t) 0xff && (data[3] == (uint8_t) 0xe0 || data[3] == (uint8_t) 0xe1))
        {
            // close old file (if open)
            if (new != NULL)
                fclose(new);
            
            // figure out filename for new file
            char* link = malloc(sizeof(char) * 8);
            
            // logic to obtain appropriate filenames
            if (num < 10)
                sprintf(link, "00%d.jpg", num);
            else
                sprintf(link, "0%d.jpg", num);
            
            num++;
            
            // open new file
            new = fopen(link, "w");
            
        }
        
        // if we've found the first block, let's start writing data to the files!
        if (new != NULL)
            fwrite(data, sizeof(data), 1, new);
    }
    
    free(data);
    return 0;
}
