#include "environment.h"

// deque	push_back is O(1)
// vector 	push_back is amortized O(1)

// Read file and convert it to a matrix,
// And list goals, obstacles and robots
scenario<bool> create_environment(string filename, std::deque<pos>& robots, std::deque<pos>& goals, std::deque<pos>& obstacles){
	string s, token;
	ifstream environment;

	scenario<bool> matrix;
	pos position;

	std::deque<pos> temp_robots, temp_goals;
	std::unordered_map<int,int> robots_map, goals_map;

	position.x = 0;
	position.y = 0;

	environment.open(filename, ios::in);

	if (environment.is_open()){

		// It passes two times for each line
		while(getline(environment, s)){
			stringstream line(s);

			std::deque<bool> aux_line;

			// Process the entire line
			while(line >> token) {
				switch(token[0]){
					case 'g':
						temp_goals.push_back(position);
						aux_line.push_back(1);
						goals_map[(token[1] - '0') - 1] = temp_goals.size()-1;
						break;
					case 'o':
						obstacles.push_back(position);
						aux_line.push_back(0);
						break;
					case 'x':
						temp_robots.push_back(position);
						aux_line.push_back(1);
						robots_map[(token[1] - '0') - 1] = temp_robots.size()-1;
						break;
					default:
						aux_line.push_back(1);
						break;
				}
				position.y++;
			}

			matrix.push_back(aux_line);

			position.x++;
			position.y = 0;

		}
	}

	environment.close();

	// Reordering goals
	for (int i = 0; i < temp_goals.size(); i++){
		goals.push_back(temp_goals[goals_map[i]]);
	}

	// Reordering robots
	for (int i = 0; i < temp_robots.size(); i++){
		robots.push_back(temp_robots[robots_map[i]]);
	}

	return matrix;
}

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

void create_new_environment(std::deque<std::deque<pos>>& moves, unordered_set<unordered_set<pos>>& new_environments){
	// Cartesian Product: http://stackoverflow.com/a/5279601
}