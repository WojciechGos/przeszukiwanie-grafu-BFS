#include "List.h"
#include <stdio.h>
#include <stdlib.h>

List * createList(){
    List *list = (List*)(malloc(sizeof(List*)));
    // List_pointer *new_node = (List_pointer *)(malloc(sizeof(List_pointer)));
    return list;
}

void add(List * list, int data)
{
    List_pointer *new_node = (List_pointer *)(malloc(sizeof(List_pointer)));
    
    // jezeli dodajemy pierwszy element do listy
    if(list->start == NULL){
        list->start = new_node;
        list->end = new_node;
        new_node->data = data;
        return;
    }
    if(new_node != NULL){
        list->end->next = new_node;
        list->end = new_node;
        new_node->data = data;
        new_node->next = NULL;
    }


}

void remove_element(List *list, int index)
{
    List_pointer * ptr = list->start, *tmp;
    int position = 0;

    while(ptr->next != NULL && (position + 1) < index){
        ptr = ptr->next;
        position++;
    }

    if(index == 0 ){
        if(list->start->next != NULL){
            tmp = ptr->next;
            free(list->start);
            list->start = tmp;
            return;
        }
        
        if(list->start->next == NULL){
            free(list->start);
            list->start = NULL;
            list->end = NULL;
            return;
        }
    }

    if (ptr->next != NULL && (position + 1) == index){
        if(ptr->next == list->end){
            free(list->end);
            list->end = ptr;
            list->end->next = NULL;
            return;

        }
        else{
            tmp = ptr->next->next;
            free(ptr->next);
            ptr->next = tmp;
            return;
        }


    }
}

bool is_list_empty(List * list){
    if(list->start == NULL)
        return true;
    return false;
}

void remove_list(List * list){
    List_pointer * ptr = list->start, *next;
    list->start = NULL;
    list->end = NULL;
    while(ptr != NULL){
        next = ptr->next;
        free(ptr);
        ptr = next;
    }
}

void print_list(List * list){
    List_pointer * ptr = list->start;
    if(ptr == NULL){
        puts("List is Empty!");
        return;
    }

    while(ptr->next != NULL){
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("%d ", ptr->data);
    puts("");
}

int at(List *list, int n){

    List_pointer * ptr = list->start;
    int i =0;
    while (ptr != NULL && i<n){
        ptr = ptr->next;
        i++;
    }
    return ptr->data;
}
