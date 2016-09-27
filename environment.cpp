#include "environment.h"

// deque	push_back is O(1)
// vector 	push_back is amortized O(1)

scenario create_environment(string filename){
	string s, token;
	ifstream environment;

	scenario matrix;

	environment.open(filename, ios::in);

	if (environment.is_open()){

		// It passes two times for each line
		while(getline(environment, s)){

			stringstream line(s);

			std::deque<string> aux_line;

			// Process the entire line
			while(line >> token) {
				aux_line.push_back(token);
			}

			matrix.push_back(aux_line);

		}
	}

	environment.close();

	return matrix;
}

void locate_objects(scenario environment, std::deque<pos>& robots, std::deque<pos>& goals, std::deque<pos>& obstacles){
	pos position, aux;

	position.x = 0;
	position.y = 0;

	for (auto line : environment){
		aux.x = position.x;
		for (auto element : line){
			aux.y = position.y;
			switch(element[0]){
				case 'g':
					goals.push_back(aux);
					break;
				case 'o':
					obstacles.push_back(aux);
					break;
				case 'x':
					robots.push_back(aux);
					break;
			}
			position.y++;
		}
		position.x++;
		position.y = 0;
	}
}