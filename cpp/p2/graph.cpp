#include "../../include/p2/graph.h"

using namespace std;

// deque	push_back is O(1)
// vector 	push_back is amortized O(1)

// Read file and convert it to a matrix,
// And list goals, obstacles and robots
adjacency_matrix create_graph(string filename){
	string s, token;
	ifstream environment;

	scenario<char> matrix;

	adjacency_matrix graph;

	deque<pos> nodes;

	int number_of_nodes = 0;
	unordered_map<pos,int> pos_map;

	std::vector<pos> moviment = load_moviment(-1,1);

	pos position;

	position.x = 0;
	position.y = 0;

	string number;

	int offset = 0;

	environment.open(filename, ios::in);

	if (environment.is_open()){

		// It passes two times for each line
		while(getline(environment, s)){
			stringstream line(s);

			std::deque<char> aux_line;

			// Process the entire line
			while(line >> token) {
				number = "";

				switch(token[0]){
					case 'x':
						aux_line.push_back(1);
						nodes.push_back(position);

						for (int i = 1; i < token.size(); i++){
							number+=token[i];
						}

						pos_map[position] = atoi(number.c_str());
						number_of_nodes++;

						if (atoi(number.c_str()) == 0){
							offset = 1;
						}

						break;
					default:
						aux_line.push_back(0);
						break;
				}
				position.y++;
			}

			matrix.push_back(aux_line);

			position.x++;
			position.y = 0;

		}
	}

	if (!number_of_nodes){
		return graph;
	}

	environment.close();

	number_of_nodes += 2;

	graph = std::vector<std::vector<int>>(number_of_nodes,std::vector<int>(number_of_nodes,0));



	position.x = matrix.size();
	position.y = matrix[0].size();

	for (pos e: nodes){
		positions p = next_moves(e, moviment, position, matrix);

		for (pos n_e : p){
			graph[pos_map[e]+offset][pos_map[n_e]+offset] = 1;

		}

		if (e.x == 0){
			graph[0][pos_map[e]+offset] = 1;
		} else {
			if (e.x == position.x-1){
				graph[pos_map[e]+offset][graph.size()-1] = 1;
			}
		}

	}

	// cout << number_of_nodes << " " << offset << endl;
	// cout << position.x << " " << position.y << endl;
	// cout << graph.size() << " " << graph[0].size() << endl;

	// cout << " \t";
	// for (int count = 0; count < graph.size(); count++){
	// 	cout << count << "\t";
	// }
	// cout << endl;
	// int count_line = 0;
	// for (std::vector<int> line : graph){
	// 	cout << count_line << "\t";
	// 	count_line++;
	// 	for (int place : line){
	// 		cout << place << "\t";
	// 	}
	// 	cout << endl;
	// }

	return graph;


}

vector<pos> load_moviment(int min, int max){
	pos aux;
	vector<pos> moviment;

	std::pair<int, int> zero = std::pair<int, int>(0,0);

	for (int i = min; i <= max; i++){
		aux.x = i;
		for (int j = min; j <= max; j++){
			aux.y = j;
			if (aux != zero){
				moviment.push_back(aux);
			}
		}
	}

	return moviment;
}