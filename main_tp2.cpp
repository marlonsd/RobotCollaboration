#include "include/environment.h"
#include "include/moviment.h"

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

	// cout << endl << "Environment:" << endl;

	// for (auto line : environment){
	// 	for (auto element : line){
	// 		cout << int(element) << "\t";
	// 	}
	// 	cout << endl;
	// }

	// cout << endl;

	// cout << "Map limit: " << environment_size.x << " " << environment_size.y << endl;

	// cout << "Objects:" << endl;
	// cout << "\tGoals: ";
	// for (auto e : goals){
	// 	cout << "(" << e.x << "," << e.y << ") ";
	// }
	// cout << endl;

	int count_possibilities = 0;

	int it = 0;

	while((it < execution_queue.size()) && !goal_found){
		robots = execution_queue[it].p;

		// Checks if goal was reached
		if (check_goal(robots, environment)){
			goal_found = true;
			continue; // Stops loop
		}

		create_new_environment(new_environments, robots, moviment, environment_size, environment);

		for (positions e : new_environments){
			std::pair<unordered_set<positions>::iterator,bool> insertion_test = possible_new_environments.insert(e);
			if (insertion_test.second){
				if (valid_scenario(robots, e, environment)){
					aux_node.p = e;
					aux_node.f = it;
					execution_queue.push_back(aux_node);
				}
			}
		}

		new_environments.clear();

		count_possibilities++;

		it++;
	}

	// cout << "Total of iterations: " << count_possibilities << endl;

	if (it == execution_queue.size()){
		cout << "No solution found." << endl;
	} else {
		vector<string> path;

		for (int i = 0; i < robots.size(); i++){
			path.push_back("]\n");
		}

		while (it >= 0){
			robots = execution_queue[it].p;
			for (int i = 0; i < robots.size(); i++){
				pos r = robots[i];

				string word = " (" + to_string(r.x+1) + "," + to_string(r.y+1) + ")";

				path[i] = word + path[i];
			}

			it = execution_queue[it].f;
		}

		for (int i = 0; i < robots.size(); i++){
			cout << "x" << i+1 << ":\t[" << path[i];
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