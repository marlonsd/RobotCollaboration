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

	deque<positions> new_environments;
	unordered_set<positions> possible_new_environments;

	node aux_node;

	deque<node> execution_queue;

	string filename = argv[1];

	pos environment_size;

	vector<pos> moviment = load_moviment(-1,1);

	environment = create_environment(filename,robots,goals);

	if (environment.size() < 1){
		cout << "It was not possible to load \"" << filename << "\"" << endl;
		exit(1);
	}

	environment_size.x = environment.size();
	environment_size.y = environment[0].size();

	possible_new_environments.insert(robots);

	aux_node.p = robots;
	aux_node.f = -1;

	execution_queue.push_back(aux_node);

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

	int count_possibilities = 0;

	int it = 0;

	while((it < execution_queue.size()) && !goal_found){
		robots = execution_queue[it].p;

		cout << "\tScenario " << count_possibilities << endl;

		for (pos e : robots){
			cout << "\t\t(" << e.x << " " << e.y << ")" << endl;
		}

		// Checks if goal was reached
		if (check_goal(robots, environment)){
			goal_found = true;
			continue; // Stops loop
		}

		for (pos e : robots){
			cout << "\tRobots: ";
			cout << "(" << e.x << "," << e.y << ") ";
			cout << endl << "\t\tMoves: ";
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
			std::pair<unordered_set<positions>::iterator,bool> insertion_test = possible_new_environments.insert(e);
			if (insertion_test.second){
				aux_node.p = e;
				aux_node.f = it;
				execution_queue.push_back(aux_node);
			}
		}

		count_possibilities++;

		// execution_queue.pop_front(); // Removes from queue when finishes expanding node
		it++;
	}

	if (it == execution_queue.size()){
		cout << "No solution found." << endl;
	} else {
		vector<string> path;

		for (int i = 0; i < robots.size(); i++){
			path.push_back("");
		}

		while (it >= 0){
			robots = execution_queue[it].p;
			for (int i = 0; i < robots.size(); i++){
				pos r = robots[i];

				string word = " (" + to_string(r.x) + "," + to_string(r.y) + ")";

				path[i] = word + path[i];
			}
		}

		for (int i = 0; i < robots.size(); i++){
			cout << "x" << i << ":" << path[i] << endl;
		}
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