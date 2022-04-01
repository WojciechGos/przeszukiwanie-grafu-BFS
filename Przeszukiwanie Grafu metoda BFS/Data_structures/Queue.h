#ifndef Queue_h
#define Queue_h

#include <stdio.h>
#include <stdbool.h>

/// Właściwa struktura kolejki
///
/// Przechowuje informacje o danych w danym węźle oraz wskaźnik na następny element kolejki
typedef struct Queue_node
{
    int data;
    struct Queue_node *next;

} Queue_node;


/// Struktura pomocnicza przechowująca wskaźnik na początek oraz koniec kolejki
///
/// ### Jak wywołać
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.c
///   Queue queue = {NULL, NULL};
///  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
typedef struct Queue
{
    Queue_node *head, *tail;

} Queue;
void push(Queue *queue, int data);
void pop(Queue *queue);
void print_queue(Queue queue);
bool is_queue_empty(Queue *queue);
int get_front_element(Queue * queue);

#endif 
