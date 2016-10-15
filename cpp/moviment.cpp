#include "../include/moviment.h"

positions next_moves(pos initial_place, vector<pos> possible_moves, pos limit, scenario<char>& environment){
	pos aux;
	positions next_steps;

	for (pos move : possible_moves){
		aux = initial_place + move;

		// Test if new position respects environment size and if the new position is on an obstacle
		if (valid_place(aux.x, aux.y, limit) && (int(environment[aux.x][aux.y]) != 0)){
			next_steps.push_back(aux);
		}
	}

	return next_steps;
}

void create_new_environment(deque<positions>& new_environments, positions& robots, vector<pos> moviment, pos limit, scenario<char>& environment){
	positions moves_temp;
	scenario<pos> aux;
	scenario<pos> moves;

	for (pos e : robots){
			positions aux_move = next_moves(e, moviment, limit, environment);
			moves.push_back(aux_move);
	}


	cartesian_product(new_environments, moves_temp, moves.begin(), moves.end());
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