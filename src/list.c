#include <stdlib.h>

#include "list.h"

LLIST *add_node(LLIST **headpp, size_t size)
{
    LLIST *node = malloc(sizeof(LLIST));
    node->data = calloc(1, size);
    node->next = node->prev = NULL;

    if (headpp != NULL)
    {
        if(*headpp != NULL)
            (*headpp)->prev = node;
        node->next = (*headpp);
    }
    *headpp = node;

    return node;
}

void delete_list(LLIST **headpp)
{
    LLIST *current;
    LLIST *tempnode;

    if (headpp != NULL)
    {
        current = *headpp;
        while (current != NULL)
        {
            tempnode = current;
            current = current->next;
            free(tempnode->data);
            free(tempnode);
        }

        *headpp = NULL;
    }
}

void delete_node(LLIST **headpp, LLIST *to_delete)
{
    if (to_delete != NULL)
    {
        if(to_delete->next != NULL)
            to_delete->next->prev = to_delete->prev;
        if(to_delete->prev != NULL)
            to_delete->prev->next = to_delete->next;
        else if (headpp != NULL)
            *headpp = to_delete->next;

        free(to_delete->data);
        free(to_delete);
    }
}
