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

struct group_pos_hash {
    inline std::size_t operator()(const unordered_set<pos, pos_hash>& v) const {
    	stringstream ss;

		for (auto e : v){
			ss << e.x << "," << e.y << ";";
		}

        return hash<string>()(ss.str());


    }
};

scenario<bool> create_environment(string filename, std::deque<pos>& robots, std::deque<pos>& goals, std::deque<pos>& obstacles);

void create_new_environment(std::deque<std::deque<pos>>& moves, unordered_set<unordered_set<pos>>& new_environments);

#endif