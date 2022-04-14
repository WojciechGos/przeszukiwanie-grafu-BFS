#ifndef Interface_h
#define Interface_h
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "Data_structures/Graph.h"
#include <stdio.h>
#include <stdbool.h>

#define EDIT_EDGES 0
#define EDIT_START 1
#define EDIT_TEMPO 2
#define PROGRAM_IS_RUNNING 3
#define PROGRAM_FINISH 4

void draw_board(Graph * graph, ALLEGRO_FONT * font, List * states, List * fake_queue, int phase);
void draw_menu(int edges, int start, int tempo, int selected, ALLEGRO_FONT * font_medium, ALLEGRO_FONT * font_big);
void handle_keyboard(ALLEGRO_EVENT events, int *amount_of_edges, int *start, int* tempo, int*select, bool *is_edges_blocked);
void generate_edges(Graph * graph, int amount_of_edges);
void fill_list_with_states(List * states);
void BFS_phase(Graph * graph, int *phase, List * state, List * fake_queue, int start);
#endif
