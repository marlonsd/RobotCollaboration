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

typedef std::deque<std::deque<string>> scenario;

struct pos{
	int x;	// Line
	int y;	// Column
};

scenario create_environment(string filename);

#endif