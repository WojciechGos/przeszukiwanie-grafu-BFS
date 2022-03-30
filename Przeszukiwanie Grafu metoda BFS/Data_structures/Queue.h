#ifndef Queue_h
#define Queue_h

#include <stdio.h>
#include <stdbool.h>

typedef struct Queue_node
{
    int data;
    struct Queue_node *next;

} Queue_node;
typedef struct Queue
{
    Queue_node *head, *tail;

} Queue;
void push(Queue *queue, int data);
void pop(Queue *queue);
void print_queue(Queue queue);
bool is_queue_empty(Queue *queue);

#endif 
