#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cstring>
#include <deque>
#include <functional>
#include <unordered_set>
#include <unordered_map> // C++11 Hash Table

struct pos{
	int x;
	int y;

	bool operator==(const pos &v) const {
		return (x == v.x &&
				y == v.y	);
	}

	bool operator!=(const pos &v) const {
		return (!(x == v.x &&
						y == v.y));
	}

	pos operator-(const pos &v){
		pos aux;

		aux.x = x-v.x;
		aux.y = y-v.y;

		return aux;
	}

	std::ostream& operator<<(std::ostream& os){
		os << "x: " << x << "y :" << y;

		return os;
	}
};

typedef std::deque<pos> positions;

namespace std {
	// Hasing: http://stackoverflow.com/a/17017281
	template <>	struct hash<pos>{
		std::size_t operator()(const pos& k) const {
			using std::size_t;
			using std::hash;
			using std::string;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return ((hash<int>()(k.x)
					^ (hash<int>()(k.y) << 1)) >> 1);
		}
	};

	template <>	struct hash<positions>{
		std::size_t operator()(const positions& k) const {
			std::stringstream ss;

			for (pos e : k){
				ss << e.x << "," << e.y << ";";
			}

			return hash<std::string>()(ss.str());
		}
	};

}

struct node{
	positions p;
	int f;
};

template <typename T>
using scenario = std::deque<std::deque<T> >;

scenario<char> create_environment(std::string filename, std::deque<pos>& robots, std::deque<pos>& goals);

bool valid_place(int x, int i, int y, int j, pos limit);
bool valid_place(int new_x, int new_y, pos limit);
bool valid_place(pos new_pos, pos limit);
bool valid_scenario(positions& places);

bool check_goal(positions& robots, scenario<char>& environment);

// Test if new_places respects problem 2 definition
bool valid_scenario(positions& old_places, positions& new_places, scenario<char> environment);

#endif