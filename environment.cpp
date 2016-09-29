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

// Read the matrix and localize objects
// void locate_objects(scenario<string> environment, std::deque<pos>& robots, std::deque<pos>& goals, std::deque<pos>& obstacles){
// 	pos position, aux;

// 	position.x = 0;
// 	position.y = 0;

// 	for (auto line : environment){
// 		aux.x = position.x;
// 		for (auto element : line){
// 			aux.y = position.y;
// 			switch(element[0]){
// 				case 'g':
// 					goals.push_back(aux);
// 					break;
// 				case 'o':
// 					obstacles.push_back(aux);
// 					break;
// 				case 'x':
// 					robots.push_back(aux);
// 					break;
// 			}
// 			position.y++;
// 		}
// 		position.x++;
// 		position.y = 0;
// 	}
// }

// void create_graph(scenario<string> environment, std::deque<pos>& robots, std::deque<pos>& goals, std::deque<pos>& obstacles){
// 	scenario<bool> matrix;	// Bool because it is just necessary to know whether its possible to access or not.
// 	pos environment_size;
// 	int environment_total;

// 	int loop = (-1,0,1);

// 	int i,j;

// 	environment_size.x = environment.size();
// 	if (environment_size.x > 0){
// 		int size_aux = environment.front().size();
// 		if (size_aux > 0){
// 			environment_size.y = environment.front().size();
// 		} else {
// 			return;
// 		}
// 	} else {
// 		return;
// 	}

// 	environment_total = environment_size.x * environment_size.y;

// 	// Initializing adjacency matrix
// 	for (i = 0; i < environment_total; i++){
// 		deque<bool> matrix_line;
// 		for (j = 0; j < environment_total; j++){
// 			matrix_line.push_back(0);
// 		}
// 		matrix.push_back(matrix_line);
// 	}

// 	i = 0;
// 	for (auto line : environment){
// 		deque<bool> matrix_line;
// 		j = 0;
// 		for (auto e : line){
// 			int place = (i*environment_size.y)+j;
// 			int aux_place;
// 			if (e == "+" || e[0] == "g"){	// Free spot
// 				for (int x : loop){
// 					for (int y : loop){
// 						aux_place = ((i+x)*environment_size.y)+(j+y);
// 					}
// 				}
// 			}

// 			j++;
// 		}
// 		matrix.push_back(matrix_line);
// 		i++;
// 	}

// }

bool valid_place(int x, int i, int y, int j, pos limit){
	bool test;

	// x+i <= limit.x && >= 0
	// y+j <= limit.y && >= 0

}