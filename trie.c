#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node {

bool check;
struct node *next[27];

} node;

node start;

int hash(char ch);
// char unhash(int ch);
void init_start(void);
void add(char *str);
bool check_str(char *str);

int hash(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    return (ch - 'a');
    else
    return 26;
}

/* char unhash(int ch)
{
    if (ch >= 0 && ch <= 25)
    return ('a' + ch);
    else
    return '\'';
} */

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
    
    backptr->check = true;
}

bool check_str(char *str)
{
    int l = strlen(str);
    node *ptr = &start, *backptr;
    
    for (int i = 0; i < l; i++)
    {
        int k = hash(str[i]);
        if (ptr->next[k] == NULL)
            return false;
        backptr = ptr;
        ptr = ptr->next[k];
    }
    
    return backptr->check;
}

/*int main(void)
{
    init_start();
    add("Hag\0Noob");

    // debug conditions

    if(check_str("Hag\0sdfg"))
        printf("Hag is there\n");
    else
        printf("Crap\n");


    return 0;
}*/
