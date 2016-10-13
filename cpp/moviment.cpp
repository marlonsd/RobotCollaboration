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

bool valid_scenario(positions& places){
	unordered_set<pos> set;

	for (pos e : places){
		set.insert(e);
	}

	return set.size() == places.size();

}

positions next_moves(pos initial_place, vector<pos> possible_moves, pos limit, scenario<char>& environment){
	pos aux;
	positions next_steps;

	for (pos move : possible_moves){
		aux.x = initial_place.x + move.x;
		aux.y = initial_place.y + move.y;

		// Test if new position respects environment size and if the new position is on an obstacle
		if (valid_place(aux.x, aux.y, limit) && environment[aux.x][aux.y]){
			next_steps.push_back(aux);
		}
	}

	return next_steps;
}

void create_new_environment(scenario<pos>& moves, deque<positions>& new_environments){
	positions moves_temp;
	scenario<pos> aux;
	cartesian_product(aux, moves_temp, moves.begin(), moves.end());

	for (positions m : aux){
		new_environments.push_back(m);
	}
}

// http://stackoverflow.com/a/5279601
void cartesian_product(deque<positions>& rvvi, positions&  rvi, deque<positions>::const_iterator me, deque<positions>::const_iterator end){ // final result, current result, current input, final input
	if(me == end) {
		// Terminal condition of the recursion.
		// Add the current result (rvi) to the total set of results (rvvvi).
		
		if (valid_scenario(rvi)){
			rvvi.push_back(rvi);
		}

		return;
	}

	const positions& mevi = *me;

	for(positions::const_iterator it = mevi.begin(); it != mevi.end(); it++) {

		rvi.push_back(*it);

		cartesian_product(rvvi, rvi, me+1, end);

		rvi.pop_back();
	}
}