#include "Interface.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <stdlib.h>
#include "Data_structures/Graph.h"
#include "Data_structures/List.h"
#include <time.h>
#include <math.h>
#include <stdbool.h>

/// promień okręgu
#define r 50

/// makro kolorów
#define COLOR_DARK_GRAY al_map_rgb(100, 100, 100)
#define COLOR_LIGHT_GRAY al_map_rgb(200, 200, 200)
#define COLOR_YELLOW al_map_rgb(237, 228, 52)
#define COLOR_RED al_map_rgb(255, 33, 66)
#define COLOR_DARK al_map_rgb(36, 36, 36)
#define COLOR_BLACK al_map_rgb(0,0,0)
#define COLOR_BLUE al_map_rgb(115,130,255)

/// stany wierzchołków na planszy, na tej podstawie rozróżnia się:
/// UNVISITED - kolor szary określa nieodwiedzone wierzchołki
#define UNVISITED 0
/// IN_QUEUE - kolor żółty określa wierzchołki znajdujące się w kolejce
#define IN_QUEUE 1
/// PROCESS - kolor  czerwony określa pobrany wierzchołek z kolejki
#define PROCESS 2
/// VISITED -  kolor ciemno szary określa wierzchołki odwiedzone
#define VISITED 3

/// VERTICES określa ilość wierzchołków na planszy
#define VERTICES 35

/// BOARD_SIZE_X oraz BOARD_SIZE_Y określa ilość wierszy oraz kolumn wierzchołków na planszy
#define BOARD_SIZE_X 7
#define BOARD_SIZE_Y 5

/// CONSTANT_CIRCLE określa punkt
#define CONSTANT_CIRCLE 35 //stała okręgu oznacza pozycje na okręgu


/// LEFT_GROUP określa grupe wiezchołków których suma id potencjalnych wierzchołków wynosi 16, więcej na ten temat jest we wstępie teoretycznym
#define LEFT_GROUP 16
/// MIDDLE_GROUP określa grupe wiezchołków których suma id potencjalnych wierzchołków wynosi 22
#define MIDDLE_GROUP 22
/// DOWN_GROUP określa grupe wiezchołków których suma id potencjalnych wierzchołków wynosi 1
#define DOWN_GROUP 1
/// RIGHT_GROUP  określa grupe wiezchołków których suma id potencjalnych wierzchołków wynosi 13
#define RIGHT_GROUP 13


/// plansza jest podzielona na siatke z punktami oddalonymi od siebie o 200px z marginesem wynoszącym 150px
/// funkcja ta pozwala na szybkie i czytelne przeliczanie pozycji
int get_real_position_on_board(int position){
    return 150+ position*200;
}

/// zamienia wartość liczbową na znaki
char * convert_int_to_char(int value){
    int length = snprintf( NULL, 0, "%d", value );
    char * str = malloc( length + 1 );
    snprintf( str, length + 1, "%d", value );
    return str;
}

///  rysuje wierzchołek na podanej wymaiginowanej pozycji x, y
///  @param id rysuje id wierzhołka na nim
///  @param state rysuje wierzhołek o określonym kolorze zależnym od jego stanu
///  @param font rysuje id podanym fontem
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


/// na podstawie id szuka wymaiginowanej pozycji x y na
/// wynik jest zapisany w zmiennych x oraz y jeśli na planszy istnieje wierzchołek o takim id
/// ~~~~~~~~.c
/// find_position_on_board(id,  &x,  &y);
/// ~~~~~~~~
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

/// rysuje krawędzie
void draw_edge(int sx, int sy, int dx, int dy){
    al_draw_line(sx, sy, dx, dy, COLOR_BLACK, 3);
}


/// rysuje plansze grafu
void draw_graph_board(Graph * graph, ALLEGRO_FONT * font, List * states){
    // drawing vertices
    int id = 0, state = 0;
    for(int y=0; y<BOARD_SIZE_Y; ++y){
        for(int x=0; x<BOARD_SIZE_X; ++x){
            state = at(states, id);
            draw_vertice(x, y, id, state, font);
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

            draw_edge(sx, sy, dx, dy);
        }
    }
    
    
    
    
}

/// rysuje żółty wskaźnik na planszy pseudo kodu
/// @param phase oznacza która linijka pesudo kodu jest wykonywana
void draw_code_pointer(int phase){
    if(phase == 0)
        return;
    if(phase == 11)
        return;
    
    int x = get_real_position_on_board(7);
    int y = 400+phase*50 - 10;
    al_draw_filled_rectangle(x, y, x+1000, y+50, COLOR_YELLOW);
}


/// rysuje plansze pseudokodu
void draw_code_board(ALLEGRO_FONT * font){
    
    int x = get_real_position_on_board(7);
    al_draw_line(x-50, 0, x-50, 1350, COLOR_RED, 20);
    char *code[14] = {
        "BFS(początek){",
            "dodaj_do_kolejki( początek )",
            "odwiedzony[ początek ] = true",
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
/// rysuje kolejke
/// @param fake_queue struktura listy jest użyta aby łatwo odczytywać wartości kolejki
void draw_queue(List * fake_queue, ALLEGRO_FONT * font ){
    int x1 = get_real_position_on_board(0) - 50;
    int y1 = get_real_position_on_board(5);
    int x2 = x1 + 60;
    int y2 = y1 + 60;
    
    int size = list_size(fake_queue);
    int id = -1;
    
    for(int i=0; i<size; ++i){
        id = at(fake_queue, i);
        al_draw_filled_rectangle(x1-5, y1-5, x2+5, y2+5, COLOR_BLACK);
        al_draw_filled_rectangle(x1, y1, x2, y2, COLOR_YELLOW);
        al_draw_text(font, COLOR_BLACK, x1+10, y1+10, 0, convert_int_to_char(id));
        x1 = x2;
        x2 += 60;
    }
    

}


///  rysuje plansze z podziałem na plansze: grafu, kolejki oraz kodu
void draw_board(Graph * graph, ALLEGRO_FONT * font, List * states, List * fake_queue, int phase){

    al_clear_to_color(COLOR_LIGHT_GRAY);
    draw_graph_board(graph, font, states);
    draw_code_pointer(phase);
    draw_code_board(font);

    draw_queue(fake_queue,font);
}


/// rysuje menu wyboru
void draw_menu(int edges, int start, int tempo, int selected, ALLEGRO_FONT * font_medium, ALLEGRO_FONT * font_big){

    
    
    int x1 = get_real_position_on_board(7);
    int y1 = 50;
    int x2 = get_real_position_on_board(11)+100;
    int y2 = get_real_position_on_board(1)-100;
    
    
    al_draw_filled_rectangle(x1, y1, x2, y2, COLOR_RED);
    

    
    if(selected == EDIT_EDGES){
        x2 = get_real_position_on_board(8)+50;
        
        al_draw_filled_rectangle(x1, y1, x2, y2, COLOR_YELLOW);
    }
    else if(selected == EDIT_START){
        x1 = get_real_position_on_board(8)+50;
        x2 = get_real_position_on_board(10)-50;
        
        al_draw_filled_rectangle(x1, y1, x2, y2, COLOR_YELLOW);
    }
    else if(selected == EDIT_TEMPO){
        x1 = get_real_position_on_board(10) -50;
        x2 = get_real_position_on_board(11) + 100;
        
        al_draw_filled_rectangle(x1, y1, x2, y2, COLOR_YELLOW);
    }
    int tx = get_real_position_on_board(7);
    int ty = 60;
    

    al_draw_text(font_medium, COLOR_BLACK, tx, ty, 0, "ILOŚĆ");
    al_draw_text(font_medium, COLOR_BLACK, tx, ty+50, 0, "CYKLI");
    al_draw_text(font_big, COLOR_BLACK, tx, ty+100, 0, convert_int_to_char(edges));
    
    tx += 350;
    
    al_draw_text(font_medium, COLOR_BLACK, tx, ty, 0, "WYBIERZ");
    al_draw_text(font_medium, COLOR_BLACK, tx, ty+50, 0, "POCZĄTEK");
    al_draw_text(font_big, COLOR_BLACK, tx, ty+100, 0, convert_int_to_char(start));
    
    tx += 250;
    
    
    al_draw_text(font_medium, COLOR_BLACK, tx, ty, 0, "PRĘDKOŚĆ");
    al_draw_text(font_medium, COLOR_BLACK, tx, ty+50, 0, "PRZETWARZANIA");
    al_draw_text(font_big, COLOR_BLACK, tx, ty+100, 0, convert_int_to_char(tempo));
    
}


/// obsługuje wydarzenia związane z klawiaturą
void handle_keyboard(ALLEGRO_EVENT events, int *amount_of_edges, int *start, int* tempo, int*select, bool *is_edges_blocked){
    
    if(*select == PROGRAM_IS_RUNNING)
        return;
    
    if(events.type == ALLEGRO_EVENT_KEY_CHAR){
        switch(events.keyboard.keycode){
            case ALLEGRO_KEY_RIGHT:
                if(*amount_of_edges < 34 && *select == EDIT_EDGES && *is_edges_blocked == false){
                    *amount_of_edges += 1;
                }
                if(*start<34 && *select == EDIT_START){
                    *start += 1;
                    *is_edges_blocked = true;
                }
                if(*tempo <20 && *select == EDIT_TEMPO){
                    *tempo += 1;
                }
                break;
                
                
            case ALLEGRO_KEY_LEFT:
                if(*amount_of_edges > 0 && *select == EDIT_EDGES ){
                    *amount_of_edges -= 1;
                }
                if(*start>0 && *select == EDIT_START){
                    *start -= 1;
                    *is_edges_blocked = true;
                }
                if(*tempo > 1 && *select == EDIT_TEMPO){
                    *tempo -= 1;
                }
                break;
                
                
            case ALLEGRO_KEY_ENTER:
                if(*select < 3)
                    *select += 1;
                break;
            case ALLEGRO_KEY_BACKSPACE:
                if(*select == 1&& *is_edges_blocked == false){
                    *select -= 1;
                }
                if(*select > 1)
                    *select -= 1;
                break;
        }
    }
}

/// identyfukuje do jakiej grupy wierzhołków należy dany wierzchołek o podanym id
int identify_vertice(int id){
    int x=-1, y=-1;
    find_position_on_board(id, &x, &y);
    

    
    int right = 1;
    int left_down = 6;
    int down = 7;
    int right_down = 8;
    
    // nadawanie ograniczeń
    if(x+1 == BOARD_SIZE_X){
        right = 0;
        right_down = 0;
    }
    if(y+1 == BOARD_SIZE_Y){
        down = 0;
        right_down = 0;
        left_down = 0;
    }
    if(x == 0){
        left_down = 0;
    }

    return right + right_down + down + left_down;
}
 
/// losuje połączenia dla danego wierzchołka
void rand_edges(Graph * graph, int root, List * edges){
    int destination, index;
    int size = list_size(edges);
    
    int amount = rand() % size;
    if(amount == 0)
        amount++;
    while(amount!=0 && size !=0){
        
        index = rand()%size;
        destination = at(edges, index) + root;
        
        remove_element(edges, index);
        add_undirected_edge(graph, root, destination);
        size = list_size(edges);
        
        amount--;
    }
    
    
}

/// wypełnia listy z których odbędą się losowania do których wierzchołków stowrzyć połączenie
void fill_edges_group(List * edges, int group){
    remove_list(edges);
    if(group == MIDDLE_GROUP){
        add(edges, 1);
        add(edges, 6);
        add(edges, 7);
        add(edges, 8);
    }
    else if(group == LEFT_GROUP){
        add(edges, 1);
        add(edges, 7);
        add(edges, 8);
    }
    else if(group == RIGHT_GROUP){
        add(edges, 7);
        add(edges, 6);
    }
    else if(group == DOWN_GROUP){
        add(edges, 1);
    }
}

///
List * select_group_of_edges(int group, List * left, List * right, List * down, List * middle){
    if(group == MIDDLE_GROUP){
        return middle;
    }
    else if(group == LEFT_GROUP){
        return left;
    }
    else if(group == RIGHT_GROUP){
        return right;
    }
    else if(group == DOWN_GROUP){
        return down;
    }
    return NULL;
}

/// generuje wierzchołki
/// @param cycles jest ro ilość losowań
void generate_edges(Graph * graph, int cycles){
  
    List vertices = {NULL, NULL};
    List edges_group_middle = {NULL, NULL};
    List edges_group_right = {NULL, NULL};
    List edges_group_down = {NULL, NULL};
    List edges_group_left = {NULL, NULL};
    List * select_edge_group = NULL;
    
    fill_edges_group(&edges_group_middle, MIDDLE_GROUP);
    fill_edges_group(&edges_group_right, RIGHT_GROUP);
    fill_edges_group(&edges_group_down, DOWN_GROUP);
    fill_edges_group(&edges_group_left, LEFT_GROUP);
    

    srand(time(NULL));

    // wypełnienie listy id wierzchołków
    for(int i=0; i<VERTICES-1; ++i){
        add(&vertices, i);
    }

    int vertice, index, size, group;
    
    for(int i=0; i<cycles; ++i){
        
        size = list_size(&vertices);
        index = rand () % size;
        vertice = at(&vertices, index);

        remove_element(&vertices, index);
        group = identify_vertice(vertice);
        
        select_edge_group = select_group_of_edges(group, &edges_group_left, &edges_group_right, &edges_group_down, &edges_group_middle);

        rand_edges(graph, vertice, select_edge_group);
        fill_edges_group(select_edge_group, group);
        
        
    }
}
/// nadaje wszystkim wierzchołkom status nieodwiedzony
void fill_list_with_states(List * states){
    for(int i=0; i<35; ++i){
        add(states, UNVISITED);
    }
}


/// zmienna ta określa obecnie przetwarzaną liste sądziedztwa w algorytmie BFS
List * current_processing_list = NULL;
/// zmienna ptr określa index w liście "current_processing_list"
/// zmienna tmp_front zapamietuje jaki wierzchołek był pobrany z kolejki
int ptr = 0, tmp_front = -1;
/// zmienna condition określa czy warunek if w pseudokodzie został spełniony
bool condition = false;


/// właściwa funkcja przeszukująca graf
/// @param state list określająca stany wierzhołków
/// @param fake_queue w tej liscie znajdują się elementy kolejki
void BFS_phase(Graph * graph, int *phase, List * state, List * fake_queue, int start){
    int front=-1, size=-1, vertice=-1;
    switch(*phase){
        case 1: // wywołanie funkcji BFS
            add(fake_queue, start);
            break;
        case 2:
            set_value_at(state, start, IN_QUEUE);
            break;
        case 3: // pętla while
            size = list_size(fake_queue);
            ptr = 0;
            if(size == 0)
                *phase = 10;
            
            break;
        case 4:
            if(tmp_front != -1){
                set_value_at(state, tmp_front, VISITED);
            }
            front = at(fake_queue, 0);
            tmp_front = front;
            printf("phase4: front:%d\n", front);
            set_value_at(state, front, PROCESS);
            current_processing_list = get_vertice(graph, front);
            puts("lista");
            print_list(current_processing_list);
            break;
        case 5:
            remove_element(fake_queue, 0);
            break;
        
        case 6: // pętla for
            size = list_size(current_processing_list);
            if(size == 0)
                *phase = 2; // przeniesienie do pętli while
            
            
            if(size <= ptr){
                puts("what");
                printf("ptf: %d, size: %d\n", ptr, size);
                *phase = 2;
            }
                
            break;
            
        case 7: // warunek if
            vertice = at(current_processing_list, ptr);
            printf("phase7: vertice:%d\n", vertice);
            if(at(state, vertice) == UNVISITED){
                condition = true;
            }
//            set_value_at(state, vertice, PROCESS);
            
            break;
            
        case 8:
            vertice = at(current_processing_list, ptr);
            printf("phase8: vertice:%d\n", vertice);
            if(condition == true){
                condition = false;
                add(fake_queue, vertice);
                set_value_at(state, vertice, IN_QUEUE);
                
            }
            else if(at(state, vertice) == IN_QUEUE){
                
            }
            else{
                set_value_at(state, vertice, VISITED);
            }
            
            break;
        case 9: // przeniesienie do pętli for
            size = list_size(current_processing_list);
            if(ptr < size){
                ptr++;
            }
            *phase = 5;
            break;
        
    }
    if(*phase == 11){
        set_value_at(state, tmp_front, VISITED);
    }
    else{
        *phase += 1;
    }
}
