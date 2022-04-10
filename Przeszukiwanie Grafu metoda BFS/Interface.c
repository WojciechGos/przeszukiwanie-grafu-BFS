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
#define PROGRAM_IS_RUNNING 3

#define VERTICES 35

#define LEFT_GROUP 16
#define MIDDLE_GROUP 22
#define DOWN_GROUP 1
#define RIGHT_GROUP 13

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
    al_draw_text(font_medium, COLOR_BLACK, tx, ty+50, 0, "KRAWĘDZI");
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

void handle_keyboard(ALLEGRO_EVENT events, int *amount_of_edges, int *start, int* tempo, int*select){
    
    if(*select == PROGRAM_IS_RUNNING)
        return;
    
    if(events.type == ALLEGRO_EVENT_KEY_CHAR){
        puts("in\n");
        switch(events.keyboard.keycode){
            case ALLEGRO_KEY_RIGHT:
                puts("?");
                if(*amount_of_edges < 102 && *select == EDIT_EDGES){
                    *amount_of_edges += 1;
                }
                if(*start<34 && *select == EDIT_START){
                    *start += 1;
                }
                if(*tempo <34 && *select == EDIT_TEMPO){
                    *tempo += 1;
                }
                break;
                
                
            case ALLEGRO_KEY_LEFT:
                if(*amount_of_edges > 0 && *select == EDIT_EDGES){
                    *amount_of_edges -= 1;
                }
                if(*start>0 && *select == EDIT_START){
                    *start -= 1;
                }
                if(*tempo > 0 && *select == EDIT_TEMPO){
                    *tempo -= 1;
                }
                break;
                
                
            case ALLEGRO_KEY_ENTER:
                if(*select < 3)
                    *select += 1;
                break;
            case ALLEGRO_KEY_BACKSPACE:
                if(*select > 0)
                    *select -= 1;
                break;
        }
    }
}






typedef struct Group{
    int e, v;
}Group;

int identify_vertice(int vertice){
    int x=-1, y=-1;
    find_position_on_board(vertice, &x, &y);
    

    
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
 

void rand_edges(Graph * graph, int root, int amount, List * edges){
    int destination, index;
    int size = list_size(&edges);
   
    
    while(amount!=0 && size !=0){
        
        index = rand()%size;
        destination = at(&edges, index);
        print_list(&edges);
        remove_element(&edges, index);
        add_undirected_edge(graph, root, destination);
        size = list_size(&edges);
        
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

int calculate_amount_of_edges_to_rand(int *amount_of_edges, int group, Group * left, Group* right, Group* down, Group* middle ){
    printf("group address: %p\n", left);
    printf("group address: %p\n", right);
    printf("group address: %p\n", down);
    printf("group address: %p\n", middle);
    
    Group * selected;
    int sum_of_edges = 0;
    if(group == MIDDLE_GROUP){
        selected = middle;
        sum_of_edges += left->e;
        sum_of_edges += right->e;
        sum_of_edges += down->e;
    }
    else if(group == LEFT_GROUP){
        selected = left;
        sum_of_edges += right->e;
        sum_of_edges += middle->e;
        sum_of_edges += down->e;
    }
    else if(group == RIGHT_GROUP){
        selected = right;
        sum_of_edges += left->e;
        sum_of_edges += middle->e;
        sum_of_edges += down->e;
    }
    else if(group == DOWN_GROUP){
        selected = down;
        sum_of_edges += left->e;
        sum_of_edges += right->e;
        sum_of_edges += middle->e;
    }
    float nominator = (float)(*amount_of_edges - sum_of_edges);
    
    float denominator = (float)(selected->v);
    float amount = ceil(nominator/denominator);
    selected->v -= 1;
    *amount_of_edges -= amount;
    return amount;
}

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

void generate_edges(Graph * graph, int amount_of_edges){
  
    List vertices = {NULL, NULL};
    List edges_group_middle = {NULL, NULL};
    List edges_group_right = {NULL, NULL};
    List edges_group_down = {NULL, NULL};
    List edges_group_left = {NULL, NULL};
    List * select_edge_group = {NULL, NULL};
    
    fill_edges_group(&edges_group_middle, MIDDLE_GROUP);
    fill_edges_group(&edges_group_right, RIGHT_GROUP);
    fill_edges_group(&edges_group_down, DOWN_GROUP);
    fill_edges_group(&edges_group_left, LEFT_GROUP);
    
    Group left = {12, 4};
    Group right = {4, 4};
    Group middle = {80, 20};
    Group down = {6,6};

    srand(time(NULL));

    // wypełnienie listy id wierzchołków
    for(int i=0; i<VERTICES-1; ++i){
        add(&vertices, i);
    }

    int vertice, index, size, group, amount;

    for(int i=0; i<VERTICES-1; ++i){
        
        size = list_size(&vertices);
        index = rand () % size;
        vertice = at(&vertices, index);
        printf("RAND VERTICE: %d\n", vertice);
        remove_element(&vertices, index);
        group = identify_vertice(vertice);
        printf("Group: %d\n", group);
        amount = calculate_amount_of_edges_to_rand(&amount_of_edges, group, &left, &right, &down, &middle);
        select_edge_group = select_group_of_edges(group, &edges_group_left, &edges_group_right, &edges_group_down, &edges_group_middle);
        
        rand_edges(graph, vertice, amount, select_edge_group);
        fill_edges_group(select_edge_group, group);
        
        
    }
}

