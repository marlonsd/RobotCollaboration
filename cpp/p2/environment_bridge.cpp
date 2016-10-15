#include "../../include/p2/environment_bridge.h"

using namespace std;

// deque	push_back is O(1)
// vector 	push_back is amortized O(1)

// Read file and convert it to a matrix,
// And list goals, obstacles and robots
scenario<bool> create_environment(string filename){
	string s, token;
	ifstream environment;

	scenario<bool> matrix;
	pos position;
	
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
					case 'x':
						aux_line.push_back(1);
						break;
					default:
						aux_line.push_back(0);
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

	return matrix;
}