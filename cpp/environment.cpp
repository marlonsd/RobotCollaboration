#include "../include/environment.h"

using namespace std;

// deque	push_back is O(1)
// vector 	push_back is amortized O(1)

// Read file and convert it to a matrix,
// And list goals, obstacles and robots
scenario<char> create_environment(string filename, std::deque<pos>& robots, std::deque<pos>& goals){
	string s, token;
	ifstream environment;

	scenario<char> matrix;
	pos position;

	std::deque<pos> temp_robots, temp_goals;
	std::unordered_map<int,int> robots_map, goals_map;

	position.x = 0;
	position.y = 0;

	environment.open(filename, ios::in);

	if (environment.is_open()){

		// It passes two times for each line
		while(getline(environment, s)){
			stringstream line(s);

			std::deque<char> aux_line;

			// Process the entire line
			while(line >> token) {
				switch(token[0]){
					case 'g':
						temp_goals.push_back(position);
						aux_line.push_back(2);
						goals_map[(token[1] - '0')] = temp_goals.size()-1;
						break;
					case 'o':
						aux_line.push_back(0);
						break;
					case 'x':
						temp_robots.push_back(position);
						aux_line.push_back(1);
						robots_map[(token[1] - '0')] = temp_robots.size()-1;
						break;
					default:
						aux_line.push_back(1);
						break;
				}
				position.y++;
			}

			matrix.push_back(aux_line);

			position.x++;
			position.y = 0;

		}
	}

	environment.close();

	// Reordering goals
	for (int i = 0; i < temp_goals.size(); i++){
		goals.push_back(temp_goals[goals_map[i]]);
	}

	// Reordering robots
	for (int i = 0; i < temp_robots.size(); i++){
		robots.push_back(temp_robots[robots_map[i]]);
	}

	return matrix;
}

bool valid_place(int x, int i, int y, int j, pos limit){
	bool test;
	int new_x, new_y;

	new_x = x+i;
	new_y = y+j;

	test = (new_x < limit.x) && (new_x >= 0);
	test = test && ((new_y < limit.y) && (new_y >= 0));

	// x+i <= limit.x && >= 0
	// y+j <= limit.y && >= 0

	return test;

}

bool valid_place(int new_x, int new_y, pos limit){
	bool test;

	test = (new_x < limit.x) && (new_x >= 0);
	test = test && ((new_y < limit.y) && (new_y >= 0));

	return test;

}

bool valid_place(pos new_pos, pos limit){
	bool test;

	test = (new_pos.x < limit.x) && (new_pos.x >= 0);
	test = test && ((new_pos.y < limit.y) && (new_pos.y >= 0));

	return test;

}

bool valid_scenario(positions& places){
	unordered_set<pos> set;

	for (pos e : places){
		set.insert(e);
	}

	return set.size() == places.size();

}

bool check_goal(positions& robots, scenario<char>& environment){

	for (pos robot : robots){
		if (int(environment[robot.x][robot.y]) != 2){
			return false;
		}
	}

	return true;
}

bool valid_scenario(positions& old_places, positions& new_places, scenario<char> environment){
	int i;

	pos limit;

	unordered_map<pos, int> position_to_number;

	vector<pair<pair<int, int>, pair<int, int> > > connect; // [(<robot1 connect to robot2>, <where the connection happens>)]

	vector<pair<int, int> > moviment = {	pair<int, int>(1,0),
											pair<int, int>(-1,0),
											// pair<int, int>(0,0),
											pair<int, int>(0,1),
											pair<int, int>(0,-1)	};

	limit.x = environment.size();
	limit.y = environment[0].size();


	for (i = 0; i < old_places.size(); i++){
		pos e = old_places[i];
		environment[e.x][e.y] = 3;
		position_to_number[e] = i;
	}

	// cout << "Stage analysis" << endl;

	// Detecting number of connections and where they occur
	for (i = 0; i < old_places.size(); i++){
		pos e = old_places[i];

		for (pair<int, int> m : moviment){
			pos p = e;

			p.x += m.first;
			p.y += m.second;

			if (valid_place(p, limit) && (environment[p.x][p.y]) == 3){
				pair<int, int> connection;
				connection.first = i;
				connection.second = position_to_number[p];

				// cout << "("<< old_places[connection.first].x << " " << old_places[connection.first].y << endl
				// 	 << old_places[connection.second].x << " " << old_places[connection.second].y << endl << endl
				// 	 << new_places[connection.first].x << " " << new_places[connection.first].y << endl
				// 	 << new_places[connection.second].x << " " << new_places[connection.second].y << ")" << endl << endl;

				if ((new_places[connection.first] - old_places[connection.first]) != (new_places[connection.second] - old_places[connection.second])){
					// cout << new_places[connection.first].x << " " << new_places[connection.first].y << endl
						 // << old_places[connection.first].x << " " << old_places[connection.first].y << endl << endl
						 // << new_places[connection.second].x << " " << new_places[connection.second].y << endl
						 // << old_places[connection.second].x << " " << old_places[connection.second].y << endl;
					// cout << "return false" << endl << endl;
					return false;
				}

				connect.push_back(pair<pair<int, int>, pair<int, int> >(connection, m));
			}
		}
	}

	// cout << "return true" << endl << endl;
	return true;
}