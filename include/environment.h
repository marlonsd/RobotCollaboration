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
};

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

}

// typedef std::deque<std::deque<string>> scenario;

typedef std::deque<pos> positions;

template <typename T>
using scenario = std::deque<std::deque<T>>;

scenario<bool> create_environment(std::string filename, std::deque<pos>& robots, std::deque<pos>& goals, std::deque<pos>& obstacles);

#endif