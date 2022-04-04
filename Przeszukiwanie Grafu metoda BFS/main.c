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

#define EDIT_EDGES 0
#define EDIT_START 1
#define EDIT_TEMPO 2


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
    Graph * graph = generate_graph(3);


  
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_init_primitives_addon();
    
   

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    int done = 0;
    int amount_of_edges = 50;  // maks to 101 krawędzi
    int start=0, tempo=0;
    
    draw_board(graph);
    draw_menu(amount_of_edges, start, tempo, 0);
    al_flip_display();

    while(!done){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

        if(events.type == ALLEGRO_EVENT_KEY_CHAR){
            switch(events.keyboard.keycode){
                case ALLEGRO_KEY_RIGHT:
                    if(amount_of_edges < 212){
                        amount_of_edges++;
                    }
                    break;
                case ALLEGRO_KEY_LEFT:
                    if(amount_of_edges > 0){
                        amount_of_edges--;
                    }
                    break;
            }
        }
        // dodaj przycisk rozpoczynający ENTER
        // dodaj przyciski umożliwiające zwolnienie lub przyśpieszenie przeszukiwania
        printf("amount_of_edges %d \n", amount_of_edges);
        draw_board(graph);
        draw_menu(amount_of_edges, start, tempo, 0);
        al_flip_display();

    }
        


    al_rest(20.);

    al_destroy_display(display);
    return 0;
}
