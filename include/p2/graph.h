#ifndef GRAPH_H
#define GRAPH_H

#include "../p1/environment.h"
#include "../p1/moviment.h"

typedef std::vector<std::vector<int>> adjacency_matrix;

adjacency_matrix create_graph(std::string filename);

vector<pos> load_moviment(int min, int max);

#endif