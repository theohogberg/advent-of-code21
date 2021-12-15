#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum dir
{
	forward,
	up,
	down
};

struct vec {
	int value;
	dir direction;
};

int depth = 0;
int horizontal = 0;

int main ()
{
	vec m = {
		.value = 2,
		.direction = dir::forward
	};
	//cout << m;
	// fetch input
	// ifstream valstream("input");
	// if (valstream.is_open())
	// {
		// string line;
		// while (getline(valstream, line))
		// {
		// 	int i = 0;
		// 	int value = stoi(line);
		// 	vals.push_back(value);
		// }
	// }



}