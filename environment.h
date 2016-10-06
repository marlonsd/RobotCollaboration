#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <deque>
#include <unordered_set>
#include <unordered_map> // C++11 Hash Table

using namespace std;

// typedef std::deque<std::deque<string>> scenario;

template <typename T>
using scenario = std::deque<std::deque<T>>;

struct pos{
	int x;	// Line
	int y;	// Column
};

// http://stackoverflow.com/a/15161034
// Hash of a pair
struct pos_hash {
    inline std::size_t operator()(const pos& v) const {
        return v.x*31+v.y;
    }
};

scenario<bool> create_environment(string filename, std::deque<pos>& robots, std::deque<pos>& goals, std::deque<pos>& obstacles);

bool valid_place(int x, int i, int y, int j, pos limit);
bool valid_place(int new_x, int new_y, pos limit);

std::deque<pos> next_moves(pos initial_place, vector<pos> possible_moves, pos limit, scenario<bool>& environment);

void create_new_environment(std::deque<std::deque<pos>>& moves, unordered_set<unordered_set<pos>>& new_environments);

#endif