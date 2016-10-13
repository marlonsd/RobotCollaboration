#include "include/environment.h"
#include "include/moviment.h"
#include <string>
#include <vector>

vector<pos> load_moviment(int min, int max);

int main(int argc, char* argv[]){
	if (argc < 2){
		cout << "File's name must be informed." << endl;
		exit(1);
	}

	bool goal_found = false;

	scenario<char> environment;
	positions robots;
	positions goals;
	// std::deque<pos> obstacles;

	// std::deque<std::deque<pos>> all_next_moves;
	deque<positions> all_next_moves;
	unordered_set<positions> possible_new_environments;

	unordered_set<pos> new_environment;
	deque<positions> new_environments;

	string filename = argv[1];

	pos environment_size;

	vector<pos> moviment = load_moviment(-1,1);

	environment = create_environment(filename,robots,goals);

	if (environment.size() < 1){
		cout << "It was not possible to load \"" << filename << "\"" << endl;
		exit(1);
	}

	possible_new_environments.insert(robots);

	environment_size.x = environment.size();
	environment_size.y = environment[0].size();

	cout << endl << "Environment:" << endl;

	for (auto line : environment){
		for (auto element : line){
			cout << int(element) << "\t";
		}
		cout << endl;
	}

	cout << endl;

	cout << "Map limit: " << environment_size.x << " " << environment_size.y << endl;

	cout << "Objects:" << endl;
	cout << "\tGoals: ";
	for (auto e : goals){
		cout << "(" << e.x << "," << e.y << ") ";
	}
	cout << endl;

	// cout << "\tObstacles: ";
	// for (auto e : obstacles){
	// 	cout << "(" << e.x << "," << e.y << ") ";
	// }
	// cout << endl;

	cout << endl;

	positions test = *possible_new_environments.begin();

	int count_possibilities = 0;
	// for (positions s : possible_new_environments){
	while(!possible_new_environments.empty() && !goal_found){
		positions robots = *possible_new_environments.begin();

		cout << "\tScenario " << count_possibilities << endl;

		for (pos e : robots){
			cout << "\t\t(" << e.x << " " << e.y << ")" << endl;
		}

		// Checks if goal was reached
		if (check_goal()){
			goal_found = true;
			continue; // Stops loop
		}

		for (pos e : robots){
			cout << "\tRobots: ";
			cout << "(" << e.x << "," << e.y << ") ";
			cout << endl << "\t\tMoves: ";
			// std::deque<pos> aux_move = next_moves(e, moviment, environment_size, environment);
			positions aux_move = next_moves(e, moviment, environment_size, environment);
			for (auto i : aux_move){
				cout << "(" << i.x << "," << i.y << ") ";
			}
			all_next_moves.push_back(aux_move);
			cout << endl;
		}
		cout << endl;

		create_new_environment(all_next_moves, new_environments);

		all_next_moves.clear();


		for (positions e : new_environments){
			possible_new_environments.insert(e);
		}

		count_possibilities++;

		possible_new_environments.erase(possible_new_environments.begin());
	}

	return 0;
}

vector<pos> load_moviment(int min, int max){
	pos aux;
	vector<pos> moviment;

	for (int i = min; i <= max; i++){
		aux.x = i;
		for (int j = min; j <= max; j++){
			aux.y = j;
			moviment.push_back(aux);
		}
	}

	return moviment;
}