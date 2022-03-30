#ifndef List_h
#define List_h

#include <stdio.h>
#include <stdbool.h>


typedef struct List_pointer{
    int data;
    struct List_pointer *next;
} List_pointer;

typedef struct List
{
    List_pointer *start, *end;
} List;

void add(List *list, int data);
void remove_element(List * list, int index);
void remove_list(List *list);
void print_list(List *list);
bool is_list_empty(List *list);
int at(List * list, int n);
List *createList();

#endif
