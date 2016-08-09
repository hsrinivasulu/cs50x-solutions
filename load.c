#include <stdio.h>
#include <stdlib.h>

#define LENGTH 45

void load(char *dictionary)
{
    FILE *book = fopen(dictionary, "r");
    char *buffer = malloc((LENGTH + 1) * sizeof(char));
    int i = 0;
    
    while (1)
    {
        buffer[i] = fgetc(book);
        if (feof(book))
        {
            buffer[i] = '\0';
            // printf("%s", buffer);
            // TODO: Put stuff to add/end
            break;
        }
        else if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            // printf("%s\n", buffer);
            // put stuff to add
            i = 0;
        }
        else
            i++;  
    }
    
    fclose(book);
    free(buffer);
}

int main(void)
{
    return 0;
}
