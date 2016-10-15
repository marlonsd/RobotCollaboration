#include "include/environment.h"
#include "include/moviment.h"

vector<pos> load_moviment();

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
	// unordered_set<node> possible_new_environments;
	unordered_set<positions> to_visit;

	node aux_node;

	deque<node> execution_queue;

	string filename = argv[1];

	pos environment_size;

	vector<pos> moviment = load_moviment();

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

	to_visit.insert(robots);

	execution_queue.push_back(aux_node);

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
			if (valid_scenario(robots, e, environment)){
				std::pair<unordered_set<positions>::iterator,bool> insertion_test = to_visit.insert(e);

				// Test if scenario is in the list to be visited
				if (insertion_test.second){
					aux_node.p = e;
					aux_node.f = it;
					execution_queue.push_back(aux_node);
				}
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

vector<pos> load_moviment(){
	pos aux;
	vector<pos> moviment;

	// Manually seleceted so it is possible to rearrange its order
	vector<std::pair<int,int> > possible_moves = {	std::pair<int,int>(0,0),
													std::pair<int,int>(0,1),
													std::pair<int,int>(0,-1),
													std::pair<int,int>(1,0),
													std::pair<int,int>(1,1),
													std::pair<int,int>(1,-1),
													std::pair<int,int>(-1,0),
													std::pair<int,int>(-1,1),
													std::pair<int,int>(-1,-1)	};

	for (std::pair<int,int> pace : possible_moves){
		aux.x = pace.first;
		aux.y = pace.second;

		moviment.push_back(aux);
	}

	// for (int i = min; i <= max; i++){
	// 	aux.x = i;
	// 	for (int j = min; j <= max; j++){
	// 		aux.y = j;
	// 		moviment.push_back(aux);
	// 	}
	// }

	return moviment;
}