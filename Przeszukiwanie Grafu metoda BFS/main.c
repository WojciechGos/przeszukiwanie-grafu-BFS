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
#include <stdbool.h>


#define screenWidth 2500
#define screenHeight 1350


int main(int argv, char **argc){
    
    ALLEGRO_DISPLAY * display;
    al_init();
    display = al_create_display(screenWidth, screenHeight);
    List states = {NULL, NULL};
    List fake_queue = {NULL, NULL};
    
    Graph * graph = create_graph(35);
    

//    print_graph_adjacent_vertices(graph, 35);
  
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_init_primitives_addon();
    
    ALLEGRO_FONT * font_small = al_load_font("CONSOLA.TTF", 32, 0);
    ALLEGRO_FONT * font_medium = al_load_font("CONSOLA.TTF", 40, 0);
    ALLEGRO_FONT * font_big = al_load_font("CONSOLA.TTF", 80, 0);
    ALLEGRO_TIMER *timer = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    
    
    fill_list_with_states(&states);
    int done = 0;
    int amount_of_cycles = 20;  // maks to 34 krawędzi
    int start=17, tempo=10, select = EDIT_EDGES;
    bool is_edges_blocked = false;
    bool block_rand = false, update = true, block_timer = false;
    int phase = 1;
    
    
    draw_board(graph, font_small, &states, &fake_queue, phase);
    draw_menu(amount_of_cycles, start, tempo, EDIT_EDGES, font_medium, font_big);
    al_flip_display();


    
    while(!done){
        ALLEGRO_EVENT events;
        al_wait_for_event(event_queue, &events);

        handle_keyboard(events, &amount_of_cycles, &start, &tempo, &select, &is_edges_blocked);
        if(select == EDIT_START && block_rand == false){
            block_rand = true;
            generate_edges(graph, amount_of_cycles);
            print_graph_adjacent_vertices(graph, 35);
//            BFS(graph, start, 35);
            
        }
        if(events.type == ALLEGRO_EVENT_TIMER)
            update = true;
        
        if(block_timer == false && select == PROGRAM_IS_RUNNING){
            block_timer = true;
            timer = al_create_timer(2./(float)tempo);
            al_register_event_source(event_queue, al_get_timer_event_source(timer));
            al_start_timer(timer);
        }
        if(update && select == PROGRAM_IS_RUNNING){
            update = false;
            BFS_phase(graph, &phase, &states, &fake_queue, start);
        }
        printf("phase:  %d\n", phase);
        if(phase == 11 && events.type == ALLEGRO_EVENT_KEY_CHAR){
            puts("?");
            al_stop_timer(timer);
            select = PROGRAM_FINISH;
            if(events.keyboard.keycode == ALLEGRO_KEY_ENTER){
                break;
            }
        }
            
            
        draw_board(graph, font_small, &states, &fake_queue, phase);
        draw_menu(amount_of_cycles, start, tempo, select, font_medium, font_big);
        
        
        
        
        
        al_flip_display();

    }
    al_destroy_display(display);
    return 0;
}
