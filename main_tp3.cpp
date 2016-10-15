#include "include/p2/environment_bridge.h"

using namespace std;

int main(int argc, char* argv[]){
	if (argc < 2){
		cout << "File's name must be informed." << endl;
		exit(1);
	}

	string filename = argv[1];

	adjacency_matrix graph = create_graph(filename);

	return 0;
}