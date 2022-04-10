#ifndef List_h
#define List_h

#include <stdio.h>
#include <stdbool.h>
/// Właściwa struktura lsty jednokierunkowej
///
///Przechowuje informacje o danych oraz wkaźniki na następne elementy
typedef struct List_pointer{
    int data;
    struct List_pointer *next;
} List_pointer;

/// List jednokierunkowa
///
/// Wskazuje na początek oraz koniec właściwej struktury listy.
///
/// ### Jak wywołać
///
///  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.c
///    List list = {NULL, NULL};
///  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
int list_size(List * list);
void set_value_at(List * list, int index, int value);

#endif
