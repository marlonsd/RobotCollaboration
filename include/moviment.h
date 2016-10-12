#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "environment.h"

using namespace std;

bool valid_place(int x, int i, int y, int j, pos limit);
bool valid_place(int new_x, int new_y, pos limit);

std::deque<pos> next_moves(pos initial_place, vector<pos> possible_moves, pos limit, scenario<bool>& environment);

#endif