#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_native_dialog.h>
#include "Data_structures/List.h"
#include "Data_structures/Queue.h"
#include "Data_structures/Graph.h"
#include "Graph_generator.h"
#include "Interface.h"

#define screenWidth 2500
#define screenHeight 1350

#define EDIT_EDGES 0
#define EDIT_START 1
#define EDIT_TEMPO 2
#define PROGRAM_IS_RUNNING 3

int main(int argv, char **argc){
    
    ALLEGRO_DISPLAY * display;
    al_init();
    display = al_create_display(screenWidth, screenHeight);
    
    Graph * graph = create_graph(35);

    generate_edges(graph, 90);
  
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_init_primitives_addon();
    
    ALLEGRO_FONT * font_small = al_load_font("CONSOLA.TTF", 32, 0);
    ALLEGRO_FONT * font_medium = al_load_font("CONSOLA.TTF", 40, 0);
    ALLEGRO_FONT * font_big = al_load_font("CONSOLA.TTF", 80, 0);
   

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    int done = 0;
    int amount_of_edges = 50;  // maks to 102 krawędzi
    int start=17, tempo=16, select = EDIT_EDGES;
    
    draw_board(graph, font_small);
    draw_menu(amount_of_edges, start, tempo, EDIT_EDGES, font_medium, font_big);
    al_flip_display();

    while(!done){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

        handle_keyboard(events, &amount_of_edges, &start, &tempo, &select);
    

        draw_board(graph, font_small);
        draw_menu(amount_of_edges, start, tempo, select, font_medium, font_big);
        al_flip_display();

    }
    al_destroy_display(display);
    return 0;
}
