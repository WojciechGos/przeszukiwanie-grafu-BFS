#include "Interface.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include "Data_structures/Graph.h"
#include "Data_structures/List.h"

#define r 50 // promień okręgu

#define COLOR_DARK_GRAY al_map_rgb(100, 100, 100)
#define COLOR_LIGHT_GRAY al_map_rgb(200, 200, 200)
#define COLOR_YELLOW al_map_rgb(237, 228, 52)
#define COLOR_RED al_map_rgb(255, 33, 66)
#define COLOR_DARK al_map_rgb(36, 36, 36)
#define COLOR_BLACK al_map_rgb(0,0,0)
#define COLOR_BLUE al_map_rgb(115,130,255)

#define UNVISITED 0
#define IN_QUEUE 1
#define PROCESS 2
#define VISITED 3

#define VERTICES 35

#define BOARD_SIZE_X 7
#define BOARD_SIZE_Y 5

#define CONSTANT_CIRCLE 35 //stała okręgu oznacza pozycje na okręgu

#define EDIT_EDGES 0
#define EDIT_START 1
#define EDIT_TEMPO 2


int get_real_position_on_board(int position){
    return 150+ position*200;
}

char * convert_int_to_char(int value){
    int length = snprintf( NULL, 0, "%d", value );
    char * str = malloc( length + 1 );
    snprintf( str, length + 1, "%d", value );
    return str;
}

///
void draw_vertice(int x, int y, int id, int state, ALLEGRO_FONT * font){
    
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

void find_position_on_board(int id, int *x, int *y){
    int tid = 0;
    for(int ty = 0; ty<BOARD_SIZE_Y; ++ty){
        for(int tx=0; tx<BOARD_SIZE_X; ++tx){
            if(tid == id){
                *x = tx;
                *y = ty;
            }
            tid++;
        }
    }
}


void draw_edge(int sx, int sy, int dx, int dy){
    al_draw_line(sx, sy, dx, dy, COLOR_BLACK, 3);
}


/// tworzy plansze grafu
void draw_graph_board(Graph * graph, ALLEGRO_FONT * font){
    // drawing vertices
    int id = 0;
    for(int y=0; y<BOARD_SIZE_Y; ++y){
        for(int x=0; x<BOARD_SIZE_X; ++x){
            draw_vertice(x, y, id, UNVISITED, font);
            id++;
        }
    }
    // drawing edges
    List * neighbours;
    int size = 0, vertice=0;
    int sx=0, sy=0, dx=0, dy=0;
    for(int root=0; root<VERTICES; ++root){
        neighbours = get_vertice(graph, root);
        size = list_size(neighbours);
        for(int j=0; j<size; ++j){
            vertice = at(neighbours, j);
            
            if(root < vertice)
                continue;
            
            sx=0;
            sy=0;
            find_position_on_board(vertice, &sx, &sy);
//            printf("from %d to %d\n", root, vertice);
//            printf("board coordinate vertice:%d, sx:%d, sy:%d\n", vertice, sx, sy);
            
            // sprawdzenie gdzie znajduje się sąsiad na planszy
            if(root == vertice+1){ // znajduje się na prawo
                dx = get_real_position_on_board(sx+1)-r;
                dy = get_real_position_on_board(sy);
                sx = get_real_position_on_board(sx)+r;
                sy = get_real_position_on_board(sy);
            }
            else if(root == vertice+7){ // znajduje się na dole
                dx = get_real_position_on_board(sx);
                dy = get_real_position_on_board(sy+1)-r;
                sx = get_real_position_on_board(sx);
                sy = get_real_position_on_board(sy)+r;
            }
            else if(root == vertice+8){ // znajduje się w prawym dolnym rogu
                dx = get_real_position_on_board(sx+1)-CONSTANT_CIRCLE;
                dy = get_real_position_on_board(sy+1)-CONSTANT_CIRCLE;
                sx = get_real_position_on_board(sx)+CONSTANT_CIRCLE;
                sy = get_real_position_on_board(sy)+CONSTANT_CIRCLE;
            }
            else if(root == vertice+6){ // znajduje się w lewym dolnym rogu
                dx = get_real_position_on_board(sx-1)+CONSTANT_CIRCLE;
                dy = get_real_position_on_board(sy+1)-CONSTANT_CIRCLE;
                sx = get_real_position_on_board(sx)-CONSTANT_CIRCLE;
                sy = get_real_position_on_board(sy)+CONSTANT_CIRCLE;
            }
//            printf("real vertice:%d, sx:%d, sy:%d dx:%d, dy:%d\n\n", vertice, sx, sy, dx, dy);
            draw_edge(sx, sy, dx, dy);
        }
    }
    
    
    
    
}

void draw_code_board(ALLEGRO_FONT * font){
    
    int x = get_real_position_on_board(7);
    al_draw_line(x-50, 0, x-50, 1350, COLOR_RED, 20);
    char *code[14] = {
        "BFS(początek){",
            "odwiedzony[ początek ] = true",
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
void draw_board(Graph * graph, ALLEGRO_FONT * font){
    al_clear_to_color(COLOR_LIGHT_GRAY);
    draw_graph_board(graph, font);
    draw_code_board(font);
}


void draw_menu(int edges, int start, int tempo, int selected, ALLEGRO_FONT * font_medium, ALLEGRO_FONT * font_big){
    
    
    int x1 = get_real_position_on_board(7);
    int y1 = 50;
    int x2 = get_real_position_on_board(11)+100;
    int y2 = get_real_position_on_board(1);
    
    
    al_draw_filled_rectangle(x1, y1, x2, y2, COLOR_RED);
    

    
    if(selected == EDIT_EDGES){
        
    }
    else if(selected == EDIT_START){
        
    }
    else if(selected == EDIT_TEMPO){
        
    }
    int tx = get_real_position_on_board(7);
    int ty = 60;
    
    al_draw_text(font_medium, COLOR_BLACK, tx, ty, 0, "ILOŚĆ");
    al_draw_text(font_medium, COLOR_BLACK, tx, ty+50, 0, "KRAWĘDZI");
    al_draw_text(font_big, COLOR_BLACK, tx, ty+100, 0, convert_int_to_char(edges));
    
    al_draw_text(font_medium, COLOR_BLACK, tx+350, ty, 0, "WYBERZ");
    al_draw_text(font_medium, COLOR_BLACK, tx+350, ty+50, 0, "START");
    
    
    al_draw_text(font_medium, COLOR_BLACK, tx+600, ty, 0, "PRĘDKOŚĆ");
    al_draw_text(font_medium, COLOR_BLACK, tx+600, ty+50, 0, "PRZETWARZANIA");
    
}
