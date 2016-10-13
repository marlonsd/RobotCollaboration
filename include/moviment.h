#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "environment.h"

using namespace std;

bool valid_place(int x, int i, int y, int j, pos limit);
bool valid_place(int new_x, int new_y, pos limit);
bool valid_scenario(positions& places);

positions next_moves(pos initial_place, vector<pos> possible_moves, pos limit, scenario<char>& environment);

void create_new_environment(deque<positions>& moves, deque<positions>& new_environments);

void cartesian_product(deque<positions>& rvvi, positions&  rvi, deque<positions>::const_iterator me, deque<positions>::const_iterator end);

#endif