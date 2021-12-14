#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<int> vals;

int main ()
{
	// fetch input
	ifstream valstream("input");
	if (valstream.is_open())
	{
		string line;
		while (getline(valstream, line))
		{
			int i = 0;
			int value = stoi(line);
			vals.push_back(value);
		}
	}

	// part 1
	int biggly = 0;
	for (int i = 0; i < vals.size(); ++i)
	{
		if (vals[i] < vals[i+1])
			biggly++;
	}
	cout << biggly << endl;
	cout << vals.size() << endl;

	// part 2
	int big = 0;
	for (int i = 0; i+2 < vals.size(); ++i)
	{
		int a = vals[i] + vals[i+1] + vals[i+2];
		int b = vals[i+1] + vals[i+2] + vals[i+3];
		//cout << a << ' ' << b << endl;
		if (a < b)
			big++;
	}
	cout << big << endl;
	cout << vals.size() << endl;

}