#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

vector<bitset<12>> vals;

int main ()
{
	// fetch input
	ifstream valstream("input");
	if (valstream.is_open())
	{
		string line;
		while (getline(valstream, line))
		{
			bitset<12> bits(line);
			vals.push_back(bits);
		}
	}

	// part 1
	int result[12] = {};
	for (int i = 0; i < vals.size(); ++i)
	{
		bitset<12> bits = vals[i];
		for (int j = 0; j < 12; ++j)
		{
			result[j] += (int)bits[j];
		}
	}
	bitset<12> final;
	for (int i = 0; i < 12; ++i)
	{
		final[i] = (result[i] >= 500) ? 1 : 0;
	}

	cout << final << endl;
	int gamma = final.to_ulong();
	cout << "g: " << gamma << endl;
	int epsilon = final.flip().to_ulong();
	cout << "e: " << epsilon << endl;
	cout << final << endl;
	cout << "g*e: " << gamma * epsilon << endl;
}
