#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <queue>
#include <memory>
#include <deque>
#include <unordered_map> // C++11 Hash Table

using namespace std;

// typedef std::deque<std::deque<string>> scenario;

template <typename T>
using scenario = std::deque<std::deque<T>>;

struct pos{
	int x;	// Line
	int y;	// Column
};

scenario<bool> create_environment(string filename, std::deque<pos>& robots, std::deque<pos>& goals, std::deque<pos>& obstacles);
// void locate_objects(scenario<string> environment, std::deque<pos>& robots, std::deque<pos>& goals, std::deque<pos>& obstacles);
// void create_graph(scenario<string> environment, std::deque<pos>& robots, std::deque<pos>& goals, std::deque<pos>& obstacles);
bool valid_place(int x, int i, int y, int j, pos limit);

#endif