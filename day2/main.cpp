#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

enum dir
{
	forward,
	up,
	down
};

static unordered_map<string, dir> const dirtable = {
	{"forward", dir::forward},
	{"up", dir::up},
	{"down", dir::down}
};

vector<string> vals;

vector<string> split (string str, char separator)
{
	vector<string> out;
	stringstream ss(str);
	string line;
	while (getline(ss, line, separator))
	{
		out.push_back(line);
	}
	return out;
}

int main ()
{
	// fetch input
	ifstream valstream("input");
	if (valstream.is_open())
	{
		string line;
		while (getline(valstream, line))
		{
			vals.push_back(line);
		}
	}

	// part 1
	int depth = 0;
	int horizontal = 0;
	for (int i = 0; i < vals.size(); ++i)
	{
		string line = vals[i];
		vector<string> com = split(line, ' ');
		string direction = com.front();
		int directionval = dirtable.at(direction);
		switch (directionval)
		{
			case dir::forward:
				horizontal += stoi(com.back());
				break;
			case dir::up:
				depth -= stoi(com.back());
				break;
			case dir::down:
				depth += stoi(com.back());
				break;
		}
	}
	cout << horizontal << endl << depth << endl;
	cout << horizontal * depth << endl;

	// part 2
	int aim = 0;
	depth = 0;
	horizontal = 0;
	for (int i = 0; i < vals.size(); ++i)
	{
		string line = vals[i];
		vector<string> com = split(line, ' ');
		string direction = com.front();
		int directionval = dirtable.at(direction);
		int x = stoi(com.back());
		switch (directionval)
		{
			case dir::forward:
				horizontal += x;
				depth += (x * aim);
				break;
			case dir::up:
				aim -= x;
				break;
			case dir::down:
				aim += x;
				break;
		}
	}
	cout << horizontal << endl << depth << endl;
	cout << horizontal * depth << endl;
}
