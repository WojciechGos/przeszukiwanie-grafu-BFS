#ifndef Graph_h
#define Graph_h
#include "List.h"
 
typedef struct Graph{
    // Lista wskaźnikow wskazujacych na listy sąsiedztwa
    List ** vertices;
} Graph;
Graph *createGraph(int vertices);
List *get_vertice(Graph *graph, int root);
void add_undirected_edge(Graph *graph, int a, int b);
void print_graph_adjacent_vertices(Graph *graph, int vertices);

#endif
