#include "Graph.h"
#include <stdlib.h>
#include "List.h"

Graph * createGraph(int vertices){
    Graph * graph = (Graph*)(malloc(sizeof(Graph)));

    graph->vertices = (malloc(sizeof(List*)*vertices));


    for(int i=0; i<vertices; ++i){


        graph->vertices[i] = createList();

        printf("%p\n" , graph->vertices[i]);
    }

    return graph;
}

List * get_vertice(Graph * graph, int root){
    return graph->vertices[root];
}

void add_undirected_edge(Graph* graph, int a, int b){

    puts("1");
    List * verticeA = get_vertice(graph, a);
    printf("list a: %p", &verticeA);
    puts("2");
    List * verticeB = get_vertice(graph, b);
    printf("list b: %p", &verticeB);

    puts("3");
    add(verticeA, b);
    puts("4");
    add(verticeB, a);
    puts("5");
}

void print_graph_adjacent_vertices(Graph* graph, int vertices){
    List * tmpVertice;
    for(int i=0; i<vertices; ++i){
        tmpVertice = get_vertice(graph, i);
        printf("root: %d ", i);
        printf("adjacent: ");
        print_list(tmpVertice);
    }
}
