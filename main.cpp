#include "environment.h"

int main(int argc, char* argv[]){
	if (argc < 2){
		cout << "File's name must be informed." << endl;
		exit(1);
	}

	scenario<bool> environment;
	std::deque<pos> robots;
	std::deque<pos> goals;
	std::deque<pos> obstacles;

	string filename = argv[1];

	environment = create_environment(filename,robots,goals,obstacles);

	cout << endl << "Environment:" << endl;
	for (auto line : environment){
		for (auto element : line){
			cout << element << "\t";
		}
		cout << endl;
	}

	cout << endl;

	// locate_objects(environment,robots,goals,obstacles);

	cout << "Objects:" << endl;
	cout << "\tRobots: ";
	for (auto e : robots){
		cout << "(" << e.x << "," << e.y << ") ";
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