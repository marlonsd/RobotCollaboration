#include "include/p2/graph.h"

using namespace std;

int main(int argc, char* argv[]){
	if (argc < 2){
		cout << "File's name must be informed." << endl;
		exit(1);
	}

	string filename = argv[1], output_filename = "output.txt";

	adjacency_matrix graph = create_graph(filename);

	ofstream output;

	output.open(output_filename);

	output << ford_fulkerson(graph, 0, graph.size()-1) << endl;

	output.close();

	return 0;
}