#ifndef Interface_h
#define Interface_h
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Data_structures/Graph.h"
#include <stdio.h>
void draw_board(Graph * graph, ALLEGRO_FONT * font);
void draw_menu(int edges, int start, int tempo, int selected, ALLEGRO_FONT * font_medium, ALLEGRO_FONT * font_big);
void handle_keyboard(ALLEGRO_EVENT events, int *amount_of_edges, int *start, int* tempo, int*select);
void generate_edges(Graph * graph, int amount_of_edges);
#endif
