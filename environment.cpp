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