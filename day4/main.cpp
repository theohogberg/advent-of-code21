#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct board {
	int plane[5][5];
};

vector<int> bingo;
vector<board> boards;

vector<int> split (string str, char separator)
{
	vector<int> out;
	stringstream ss(str);
	string line;
	while (getline(ss, line, separator))
	{
		out.push_back(stoi(line));
	}
	return out;
}

int main ()
{
	// fetch input
	ifstream inpstream("input");
	if (inpstream.is_open())
	{
		string line;
		bool init = true;
		while (getline(inpstream, line))
		{
			if (init)
			{
				bingo = split(line, ',');
				for (int i = 0; i < bingo.size(); ++i)
				{
					cout << bingo[i];
				}
				init = false;
			}
			// add board
		}
	}
}
