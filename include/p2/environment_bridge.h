#ifndef ENVIRONMENT_BRIDGE_H
#define ENVIRONMENT_BRIDGE_H

#include "../p1/environment.h"
#include "../p1/moviment.h"

typedef std::vector<std::vector<int>> adjacency_matrix;

adjacency_matrix create_graph(std::string filename);

vector<pos> load_moviment(int min, int max);

#endif