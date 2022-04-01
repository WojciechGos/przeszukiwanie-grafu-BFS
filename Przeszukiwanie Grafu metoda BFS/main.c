//
//  main.c
//  Przeszukiwanie Grafu metoda BFS
//
//  Created by Wojtek Gos on 20/03/2022.
//

#include "main.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "Data_structures/List.h"
#include "Data_structures/Queue.h"
#include "Data_structures/Graph.h"

int main(int argv, char **argc){
    

    Graph * graph = create_graph(4);
    
    add_undirected_edge(graph, 0, 3);
    add_undirected_edge(graph, 0, 1);
    add_undirected_edge(graph, 1, 2);
    
    print_graph_adjacent_vertices(graph, 4);
    
    BFS(graph, 4, 0);
    
//    ALLEGRO_DISPLAY * display;
//    al_init();
//    display = al_create_display(2500, 1400);
//    al_clear_to_color(al_map_rgb(255, 0, 255));
//
//
//    al_draw_filled_circle(300, 200, 500, al_map_rgb(255, 0, 0));
//
//    al_init_font_addon();
//    al_init_ttf_addon();
//    ALLEGRO_FONT * font24 = al_load_font("arial.ttf", 24, 0);
////    al_draw_text(font24, al_map_rgb(0, 0, 255), 100, 100, 0, "Hello World");
//
////    al_flip_display();
//
////    while(){
////
////    }
//
//
//
//
//
//    al_rest(10.);
//
//    al_destroy_display(display);
    return 0;
}
