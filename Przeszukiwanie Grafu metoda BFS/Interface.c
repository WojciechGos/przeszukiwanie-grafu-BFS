#include "Interface.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>


#define r 50 // promień okręgu
#define COLOR_DARK_GRAY al_map_rgb(100, 100, 100)
#define COLOR_LIGHT_GRAY al_map_rgb(200, 200, 200)
#define COLOR_YELLOW al_map_rgb(237, 228, 52)
#define COLOR_RED al_map_rgb(255, 33, 66)
#define COLOR_DARK al_map_rgb(36, 36, 36)

#define UNVISITED 0
#define IN_QUEUE 1
#define PROCESS 2
#define VISITED 3

int get_real_position_on_board(int position){
    return 150+ position*200;
}

char * convert_int_to_char(int id){
    int length = snprintf( NULL, 0, "%d", id );
    char * str = malloc( length + 1 );
    snprintf( str, length + 1, "%d", id );
    return str;
}

///
void set_vertice(int x, int y, int id, int state, ALLEGRO_FONT * font){
    
    x = get_real_position_on_board(x);
    y = get_real_position_on_board(y);
    if(state == UNVISITED){ // nie odwiedzony
        al_draw_filled_circle(x, y, r, COLOR_DARK_GRAY);
    }
    else if(state == IN_QUEUE) { // w kolejce
        al_draw_filled_circle(x, y, r, COLOR_YELLOW);
    }
    else if(state == PROCESS) { // przetwarzany
        al_draw_filled_circle(x, y, r, COLOR_RED);
    }
    else if(state == VISITED){ // odwiedzony
        al_draw_filled_circle(x, y, r, COLOR_DARK);
    }

    al_draw_text(font, al_map_rgb(0, 0, 0), x-15, y-15, 0, convert_int_to_char(id));
}


/// tworzy plansze grafu
void create_graph_board(int edges, ALLEGRO_FONT * font){
    int id = 0;
    for(int y=0; y<5;++y){
        for(int x=0; x<7; ++x){
            set_vertice(x, y, id, UNVISITED, font);
            id++;
        }
    }
}

void create_code_board(ALLEGRO_FONT * font){
    int x = get_real_position_on_board(7);
    al_draw_line(x-50, 0, x-50, 1350, COLOR_RED, 20);
    
    x = get_real_position_on_board(7);
    char *code[14] = {
        "BFS(początek){",
            "odwiedzony[ start ] = true",
            "dodaj_do_kolejki( początek )",
            "while( jeżeli_kolejka_nie_jest_pusta() ){",
                "wierzchołek = front_kolejki()",
                "usuń_element_z_kolejki()",
                "for( dla każdego sąsiada){",
                    "if(czy_został_odwiedzony(sąsiad) == fałsz){",
                        "odwiedzony[sąsiad] = true",
                        "dodaj_do_kolejki( sąsiad )",
                    "}",
                "}",
            "}",
        "}"
        
    };
    int tab[] = {
        0,
        50,
        50,
        50,
        100,
        100,
        100,
        150,
        200,
        200,
        150,
        100,
        50,
        0
        
    };
    for(int i=0; i<14; ++i){
        al_draw_text(font, al_map_rgb(0, 0, 0), tab[i]+x, 400+i*50, 0, code[i]);
    }
    
}

///  tworzy plansze z podziałem na plansze: grafu, kolejki oraz kodu
void create_board(int edges){
    ALLEGRO_FONT * font = al_load_font("CONSOLA.TTF", 32, 0);
    al_clear_to_color(COLOR_LIGHT_GRAY);
    create_graph_board(edges, font);
    create_code_board(font);
}
    

