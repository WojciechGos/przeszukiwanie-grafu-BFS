#include "Queue.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void push(Queue *queue, int data) {
    Queue_node *new_node = (struct Queue_node *)
    malloc(sizeof(struct Queue_node));
    if(NULL != new_node) {
        new_node -> data = data;
        new_node -> next = NULL;
        if (NULL == queue -> head)
            queue -> head = queue -> tail = new_node;
        else {
            queue -> tail -> next = new_node;
            queue -> tail = new_node;
        }
    }
}
void pop(Queue *queue) {
    if (NULL != queue -> head) {
        Queue_node *tmp = queue -> head -> next;
        free(queue -> head);
        queue -> head = tmp;
        if (NULL == tmp)
            queue -> tail = NULL;
   
    }
}

void remove_queue(Queue * queue){
    Queue_node * ptr = queue->head, *next;
    while(ptr != NULL){
        next = ptr->next;
        free(ptr);
        ptr = next;
    }
    queue->head = NULL;
    queue->tail = NULL;

}

bool is_queue_empty(Queue *queue){
    if(queue->head == NULL)
        return true;
    return false;
}
 void print_queue(Queue queue) {
    for (; NULL != queue.head; queue.head = queue.head -> next)
        printf("%d ", queue.head -> data);
    printf("\n");
    
}
