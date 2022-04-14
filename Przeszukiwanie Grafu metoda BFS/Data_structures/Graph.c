#include "Graph.h"
#include <stdlib.h>
#include "List.h"
#include "Queue.h"

#define VERTICES 35

/// funckcja alokuje w pamięci graf
/// @param vertices - przyjmuje ilość wierzchowłków jakie ma zaalokować
/// ### Jak korzystać
///   ~~~~~~~~~~~~~~~~~~~.c
///   Graph * graph = create_graph(vertices);
///   ~~~~~~~~~~~~~~~~~~~
///  @return zwraca wskaźnik na komórkę pamięci grafu
Graph * create_graph(int vertices){
    Graph * graph = (Graph*)(malloc(sizeof(Graph)));

    graph->vertices = (malloc(sizeof(List*)*vertices));

    for(int i=0; i<vertices; ++i){
        graph->vertices[i] = createList();
    }

    return graph;
}

/// Funkcja ta zwraca wskaźnik na liste sąsiedztwa danego wierzchołka
///
/// Jest skróceniem zapisu
/// ~~~~~~~~.c
/// graph->vertices[root];
/// ~~~~~~~~
List * get_vertice(Graph * graph, int root){
    return graph->vertices[root];
}

/// Funckja ta dodaje krawędź nie skierowaną do grafu z wierzchołka a do wierzchołka b
/// @warning funkcja alokuje dokładnie tyle wierzchołków ile jest podane w funkcji create_graph, przy czym pierwszy element ma index 0 a ostatni vertices-1
void add_undirected_edge(Graph* graph, int a, int b){
    List * verticeA = get_vertice(graph, a);
    List * verticeB = get_vertice(graph, b);
    
    add(verticeA, b);
    add(verticeB, a);
}
/// wyświetla listę sąsiedztwa każdego wierzchołka w konsoli
void print_graph_adjacent_vertices(Graph* graph, int vertices){
    List * tmpVertice;
    for(int i=0; i<vertices; ++i){
        tmpVertice = get_vertice(graph, i);
        printf("root: %d ", i);
        printf("adjacent: ");
        print_list(tmpVertice);
    }
}

void fill_list(List * list, int vertices){
    for(int i=0; i<vertices; ++i){
        add(list, 0);
    }
    
}



void BFS(Graph * graph, int start, int vertices){
    ///lista ta przetrzymuje informacje czy dany wierzchołek został odwiedzony czy nie
    List visited = {NULL, NULL}, *currentProcesedList = NULL;
    int size = 0, vertice = -1, front;
    Queue queue = {NULL, NULL};
    
    fill_list(&visited, vertices);

    set_value_at(&visited, start, 1);
    push(&queue, start);

    while(!is_queue_empty(&queue)){
        front =  get_front_element(&queue);
        currentProcesedList = get_vertice(graph, front);
        pop(&queue);
        
        size = list_size(currentProcesedList);
        
        for(int i=0; i<size; ++i){
            vertice = at(currentProcesedList, i);
            printf("vertice: %d for: %d\n", front, vertice);

            if(at(&visited, vertice) == 0){
                set_value_at(&visited, vertice, 1);
                push(&queue, vertice);
            }
        }
    }
}

