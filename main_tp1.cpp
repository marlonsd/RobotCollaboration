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
	// positions goals;

	deque<positions> new_environments;
	unordered_set<node> possible_new_environments;
	unordered_set<positions> visited;

	node aux_node;

	deque<node> execution_queue;

	string filename = argv[1];

	pos environment_size;

	vector<pos> moviment = load_moviment(-1,1);

	environment = create_environment(filename,robots);

	if (environment.size() < 1){
		cout << "It was not possible to load \"" << filename << "\"" << endl;
		exit(1);
	}

	environment_size.x = environment.size();
	environment_size.y = environment[0].size();

	// possible_new_environments.insert(robots);

	aux_node.p = robots;
	aux_node.f = -1;

	// possible_new_environments.insert(aux_node);

	execution_queue.push_back(aux_node);

	int it = 0;

	while((it < execution_queue.size()) && !goal_found){
		robots = execution_queue[it].p;

		std::pair<unordered_set<positions>::iterator,bool> insertion_test = visited.insert(robots);

		cout << "Iteration " << it << endl;

		// Tests if scenario have been visited before
		if (!insertion_test.second){
			it++;
			continue;
		}

		// Checks if goal was reached
		if (check_goal(robots, environment)){
			cout << "found" << endl;
			goal_found = true;
			continue; // Stops loop
		}

		create_new_environment(new_environments, robots, moviment, environment_size, environment);

		for (positions e : new_environments){
			unordered_set<positions>::iterator visited_test = visited.find(e);

			// Test if scenario is in the list to be visited
			if (visited_test == visited.end()){
				aux_node.p = e;
				aux_node.f = it;
				
				execution_queue.push_back(aux_node);
			}
		}

		new_environments.clear();

		it++;
	}

	if (it >= execution_queue.size()){
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

				string word = " (" + to_string(r.x) + "," + to_string(r.y) + ")";

				path[i] = word + path[i];
			}

			it = execution_queue[it].f;
		}

		for (int i = 0; i < robots.size(); i++){
			cout << "x" << i << ":\t[" << path[i];
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