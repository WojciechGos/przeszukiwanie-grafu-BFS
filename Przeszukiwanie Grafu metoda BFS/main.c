#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "Data_structures/List.h"
#include "Data_structures/Queue.h"
#include "Data_structures/Graph.h"
#include "Interface.h"

#define screenWidth 2500
#define screenHeight 1350


int main(int argv, char **argc){
    
//    int vertices = 5;
//    Graph * graph = create_graph(vertices);
//
//    add_undirected_edge(graph, 0, 3);
//    add_undirected_edge(graph, 0, 1);
//    add_undirected_edge(graph, 1, 2);
//    add_undirected_edge(graph, 4, 2);
//
//    print_graph_adjacent_vertices(graph, vertices);
//
//    BFS(graph, 0, vertices);
    
    ALLEGRO_DISPLAY * display;
    al_init();
    display = al_create_display(screenWidth, screenHeight);
    


  
    al_init_font_addon();
    al_init_ttf_addon();
    
    ALLEGRO_FONT * font = al_load_font("CONSOLA.TTF", 32, 0);
//    al_draw_text(font, al_map_rgb(0, 0, 255), 100, 100, 0, "Hello World");
    create_board(5);
    al_flip_display();
//
////    while(){
////
////    }
//
//
//
//
//
    al_rest(20.);

    al_destroy_display(display);
    return 0;
}
