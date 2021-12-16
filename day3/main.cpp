#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bitset>

using namespace std;

vector<bitset<5>> vals;

vector<bitset<5>> getOxy (vector<bitset<5>> vs, short o)
{
	if (vs.size() == 1)
	{
		return vs;
	}

	vector<bitset<5>> zeros;
	vector<bitset<5>> ones;
	for (int i = 0; i < vs.size(); ++i)
	{
		if (vs[i][o] == 0)
		{
			zeros.push_back(vs[i]);
		}
		else
		{
			ones.push_back(vs[i]);
		}
	}

	// check biggly
	short zeros_sz = zeros.size();
	short ones_sz = ones.size();
	if (zeros_sz > ones_sz)
	{
		return getOxy(zeros, o-1);
	}
	else if (zeros_sz < ones_sz)
	{
		return getOxy(ones, o-1);
	}
	else // if all else is equal bring back ones
	{
		return getOxy(ones, o-1);
	}
}

vector<bitset<5>> getCo2 (vector<bitset<5>> vs, short o)
{
	if (vs.size() == 1)
	{
		return vs;
	}

	vector<bitset<5>> zeros;
	vector<bitset<5>> ones;
	for (int i = 0; i < vs.size(); ++i)
	{
		if (vs[i][o] == 0)
		{
			zeros.push_back(vs[i]);
		}
		else
		{
			ones.push_back(vs[i]);
		}
	}

	// check biggly
	short zeros_sz = zeros.size();
	short ones_sz = ones.size();
	if (zeros_sz < ones_sz)
	{
		return getCo2(zeros, o-1);
	}
	else if (zeros_sz > ones_sz)
	{
		return getCo2(ones, o-1);
	}
	else // if all else is equal bring back zeroes
	{
		return getCo2(zeros, o-1);
	}
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
			bitset<5> bits(line);
			vals.push_back(bits);
		}
	}

	// part 1
	// int result[5] = {};
	// for (int i = 0; i < vals.size(); ++i)
	// {
	// 	bitset<5> bits = vals[i];
	// 	for (int j = 0; j < 5; ++j)
	// 	{
	// 		result[j] += (int)bits[j];
	// 	}
	// }
	// bitset<5> final;
	// for (int i = 0; i < 5; ++i)
	// {
	// 	final[i] = (result[i] >= 500) ? 1 : 0;
	// }
	// cout << final << endl;
	// int gamma = final.to_ulong();
	// cout << "g: " << gamma << endl;
	// int epsilon = final.flip().to_ulong();
	// cout << "e: " << epsilon << endl;
	// cout << final << endl;
	// cout << "g*e: " << gamma * epsilon << endl;

	// part 2 recursion
	vector<bitset<5>> oxyvec;
	bitset<5> oxybits;
	oxyvec = getOxy(vals, 4);
	oxybits = oxyvec[0];
	cout << oxybits << '\n' << oxybits.to_ulong() << endl;

	vector<bitset<5>> co2vec;
	bitset<5> co2bits;
	co2vec = getCo2(vals, 4);
	co2bits = co2vec[0];
	cout << co2bits << '\n' << co2bits.to_ulong() << endl;

	// cout << oxybits.to_ulong() * co2bits.to_ulong() << endl;
}
