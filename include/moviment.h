#ifndef MOVIMENT_H
#define MOVIMENT_H

#include "environment.h"

using namespace std;

positions next_moves(pos initial_place, vector<pos> possible_moves, pos limit, scenario<char>& environment);

void create_new_environment(deque<positions>& new_environments, positions& robots, vector<pos> moviment, pos limit, scenario<char>& environment);

void cartesian_product(deque<positions>& rvvi, positions&  rvi, deque<positions>::const_iterator me, deque<positions>::const_iterator end);

#endif