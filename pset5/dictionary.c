/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"

typedef struct node {

bool check;
struct node *next[27];

} node;

node start;
int n = 0;

int hash(char ch);
void init_start(void);
void add(char *str);
bool check_str(char *str);
void destroy(node *ptr);

int hash(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    return (ch - 'a');
    else
    return 26;
}

void init_start(void)
{
    start.check = false;
    for(int i = 0; i < 27; i++)
    {
        start.next[i] = NULL;
    }
}

void add(char *str)
{
    int l = strlen(str);
    
    node *ptr = &start, *backptr;
    
    for (int i = 0; i < l; i++)
    {
        int k = hash(str[i]);
        
        if(ptr->next[k] == NULL)
        {
            ptr->next[k] = malloc(sizeof(node));
            node* new = ptr->next[k];
            
            // initialising
            
            new->check = false;
            for (int i = 0; i < 27; i++)
                new->next[i] = NULL;
        }
        
        backptr = ptr;
        ptr = ptr->next[k];
    }
    
    ptr->check = true;
}

bool check_str(char *inp)
{
    int l = strlen(inp);
    
    char *str = malloc((LENGTH + 1) * sizeof(char));
    
    strcpy(str, inp);
    
    for (int i = 0; i < l; i++)
    {
        str[i] = tolower(inp[i]);
    }
    
    node *ptr = &start, *backptr;
    
    for (int i = 0; i < l; i++)
    {
        int k = hash(str[i]);
        if (ptr->next[k] == NULL)
        {
            free(str);
            return false;
        }
        backptr = ptr;
        ptr = ptr->next[k];
    }
    
    free(str);
    
    return ptr->check;
}

void destroy(node *ptr)
{
    for(int i = 0; i < 27; i++)
    {
        if(ptr->next[i] != NULL)
            destroy(ptr->next[i]);
        
    }
    
    free(ptr);
}

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    return check_str((char*)word);
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE *book = fopen(dictionary, "r");
    if (book == NULL)
    {
        printf("Unable to open book :(\n");
        return false;
    }
    
    init_start();
    
    char *buffer = malloc((LENGTH + 1) * sizeof(char));
    int i = 0;
    
    while (1)
    {
        buffer[i] = fgetc(book);
        if (feof(book))
        {
            buffer[i] = '\0';
            // printf("%s", buffer);
            add(buffer);
            break;
        }
        else if (buffer[i] == '\n')
        {
            buffer[i] = '\0';
            // printf("%s\n", buffer);
            add(buffer);
            n++;
            i = 0;
        }
        else
            i++;  
    }
    
    fclose(book);
    free(buffer);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return n;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0; i < 27; i++)
    {
        if(start.next[i] != NULL)
        {
            destroy(start.next[i]);
        }
    }
    return true;
}
