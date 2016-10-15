#ifndef ENVIRONMENT_BRIDGE_H
#define ENVIRONMENT_BRIDGE_H

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

#include "../p1/environment.h"

scenario<bool> create_environment(std::string filename);

#endif