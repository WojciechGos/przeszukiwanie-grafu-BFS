#include "List.h"
#include <stdio.h>
#include <stdlib.h>
/// Funckja alokuje liste w pamięci
/// 
/// @return Zwraca wskaźnik na zaalokowaną komórkę pamięci
/// @warning Nie ma potrzeby używać przy pojedynczych Listach, wtedy najlepiej użyć add()
/// @see add(List * list, int data)
List * createList(){
    List *list = (List*)(malloc(sizeof(List)));
    list->start = NULL;
    list->end = NULL;
    return list;
}

///Dodaje do listy  dane na jej koniec
///
///###Jak korzystać
///  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~.c
///     add(&list, data);
///  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void add(List * list, int data)
{
    List_pointer *new_node = (List_pointer *)(malloc(sizeof(List_pointer)));
    
    // jezeli dodajemy pierwszy element do listy
    if(list->start == NULL){
        list->start = new_node;
        list->end = new_node;
        new_node->data = data;
        new_node->next = NULL;
        return;
    }
    if(new_node != NULL){
        list->end->next = new_node;
        list->end = new_node;
        new_node->data = data;
        new_node->next = NULL;
    }


}
/// Usuwa element na wybranej pozycji listy
///
///  @attention Jeśli wskazany index jest większy niż ilość elementów w tablicy to funkcja usunie ostatni element
void remove_element(List *list, int index)
{
    List_pointer * ptr = list->start, *tmp;
    int position = 0;

    while(ptr->next != NULL && (position + 1) < index){
        ptr = ptr->next;
        position++;
    }
    
    if(index == 0 ){
        if(list->start == list->end){
            tmp = list->start;
            free(tmp);
            list->start = NULL;
            list->end = NULL;
            
            
            return;
        }
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

/// Funkcja ta sprawdza czy lista jest pusta
bool is_list_empty(List * list){
    if(list->start == NULL)
        return true;
    return false;
}
/// Funkcja ta usuwa całą zawartość listy
///
/// @attention Po tej operacji dalej można używać listy
void remove_list(List * list){
    if(list->start == NULL || list->end == NULL)
        return;
        
    List_pointer * ptr = list->start, *next;
    list->start = NULL;

    while(ptr != NULL){
        next = ptr->next;
        free(ptr);
        ptr = next;
    }
//    free(list->end);
    list->end = NULL;
}

/// Wyświetla zawartość podanej listy przez parametr
void print_list(List * list){
    List_pointer * ptr = list->start;
    
    if(ptr == NULL){
        puts("List is Empty!");
        return;
    }

    while(ptr != NULL){
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }

    puts("");
}

/// Zwraca zawartość elementu listy na danej pozycji
///
/// @attention Jeśli index jest większy niż ilość elementów tablicy to funkcja ta zwróci ostatni element
/// @warning Nie używać gdy lista jest pusta!
int at(List *list, int index){
    
    List_pointer * ptr = list->start;
    if(ptr == NULL)
        return -1;
    int i =0;
    while (ptr->next != NULL && i<index){
        ptr = ptr->next;
        i++;
    }
    return ptr->data;
}

/// Funkcja ta zwraca ilość elementów w liście
int list_size(List * list){
    int counter = 0;
    if(list == NULL)
        return 0;
    List_pointer * ptr = list->start;
    while(ptr != NULL){
        ptr = ptr->next;
        counter ++;
    }
    return counter;
}

void set_value_at(List * list, int index, int value){
    List_pointer * ptr = list->start;
    int counter = 0;
    if(ptr == NULL)
        return;
    
    while(ptr->next != NULL && counter < index){
        counter++;
        ptr = ptr->next;
    }
    
    if(counter < index)
        return;

    ptr->data = value;
}
