#include "include/environment.h"
#include "include/moviment.h"

vector<pos> load_moviment(int min, int max);

int main(int argc, char* argv[]){
	if (argc < 2){
		cout << "File's name must be informed." << endl;
		exit(1);
	}

	scenario<bool> environment;
	std::deque<pos> robots;
	std::deque<pos> goals;
	std::deque<pos> obstacles;

	std::deque<std::deque<pos>> all_next_moves;

	unordered_set<pos, pos_hash> new_environment;
	unordered_set<unordered_set<pos, pos_hash>, group_pos_hash> new_environments;

	string filename = argv[1];

	pos environment_size;

	vector<pos> moviment = load_moviment(-1,1);

	environment = create_environment(filename,robots,goals,obstacles);

	if (environment.size() < 1){
		cout << "It was not possible to load \"" << filename << "\"" << endl;
		exit(1);
	}

	environment_size.x = environment.size();
	environment_size.y = environment[0].size();

	cout << endl << "Environment:" << endl;
	for (auto line : environment){
		for (auto element : line){
			cout << element << "\t";
		}
		cout << endl;
	}

	cout << endl;

	cout << "Map limit: " << environment_size.x << " " << environment_size.y << endl;

	cout << "Objects:" << endl;
	for (auto e : robots){
		cout << "\tRobots: ";
		cout << "(" << e.x << "," << e.y << ") ";
		cout << endl << "\t\tMoves: ";
		std::deque<pos> aux_move = next_moves(e, moviment, environment_size, environment);
		for (auto i : aux_move){
			cout << "(" << i.x << "," << i.y << ") ";
		}
		all_next_moves.push_back(aux_move);
		cout << endl;
	}
	cout << endl;

	cout << "\tGoals: ";
	for (auto e : goals){
		cout << "(" << e.x << "," << e.y << ") ";
	}
	cout << endl;

	cout << "\tObstacles: ";
	for (auto e : obstacles){
		cout << "(" << e.x << "," << e.y << ") ";
	}
	cout << endl;

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