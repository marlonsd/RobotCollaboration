#include "../include/moviment.h"

bool valid_place(int x, int i, int y, int j, pos limit){
	bool test;
	int new_x, new_y;

	new_x = x+i;
	new_y = y+j;

	test = (new_x < limit.x) && (new_x >= 0);
	test = test && ((new_y < limit.y) && (new_y >= 0));

	// x+i <= limit.x && >= 0
	// y+j <= limit.y && >= 0

	return test;

}

bool valid_place(int new_x, int new_y, pos limit){
	bool test;

	test = (new_x < limit.x) && (new_x >= 0);
	test = test && ((new_y < limit.y) && (new_y >= 0));

	return test;

}

std::deque<pos> next_moves(pos initial_place, vector<pos> possible_moves, pos limit, scenario<bool>& environment){
	pos aux;
	std::deque<pos> next_steps;

	for (pos move : possible_moves){
		aux.x = initial_place.x + move.x;
		aux.y = initial_place.y + move.y;

		if (valid_place(aux.x, aux.y, limit) && environment[aux.x][aux.y]){
			next_steps.push_back(aux);
		}
	}

	return next_steps;
}

