#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int enqueue(struct studentqueue *q, const char *name)
{
    int nameLength = 0;
    while(q->next != NULL)
        q = q->next;
    const char* nameCopy = name;
    while(*nameCopy++)
        nameLength++;
    struct studentqueue* newNode = malloc(sizeof(struct studentqueue));
    if(newNode == NULL)
        return 0;
    newNode->name = malloc(nameLength+1);
    if(newNode->name == NULL)
        return 0;
    strcpy(newNode->name, name);
    newNode->next = NULL;
    q->next = newNode;

    return 1;
}

int dequeue(struct studentqueue *q, char *buffer, unsigned int size)
{
    //oletus: q on aina empty node (?)
    struct studentqueue* qEmpty = q;
    if(q->next != NULL)
        q = q->next;
    else
        return 0;
    //nyt q = poistettava node

    strncpy(buffer, q->name, size-1);
    if(q->next != NULL)
        qEmpty->next = q->next;
    else
        qEmpty->next = NULL;
    free(q->name);
    free(q);
    return 1;
}
