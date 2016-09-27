#include "environment.h"

int main(int argc, char* argv[]){
	if (argc < 2){
		cout << "File's name must be informed." << endl;
		exit(1);
	}

	scenario environment;

	string filename = argv[1];

	environment = create_environment(filename);

	for (auto line : environment){
		for (auto element : line){
			cout << element << " ";
		}
		cout << endl;
	}

	return 0;
}