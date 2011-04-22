#ifndef LIST_INC
#define LIST_INC

typedef struct LList
{
   struct LList *next;
   struct LList *prev;
   void *data;
} LLIST;

LLIST *add_node(LLIST **, size_t); //adds a new node to the list
void delete_list(LLIST **);      //removes the entire list
void delete_node(LLIST **, LLIST *);  //removes one node from the list

#endif
