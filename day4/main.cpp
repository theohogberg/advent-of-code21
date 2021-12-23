#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct board {
	char plane[5][5];
	bool init = false;
	bool bingo = false;
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

vector<int> splitWS(string &input) {
  istringstream buffer(input);
  vector<string> strvector;

  copy(istream_iterator<string>(buffer), istream_iterator<string>(), back_inserter(strvector));
  vector<int> intvector(strvector.size());

  for (int i = 0; i < strvector.size(); ++i)
  {
		intvector[i] = stoi(strvector[i]);
  }

  return intvector;
}

board checkBingo (board* b)
{
	for (int i = 0; i < 5; ++i)
	{
		// row
		for (int j = 0; j < 5; ++j)
		{
			if (b->plane[i][j] == -1)
			{
				if (j == 4)
				{
					// bingo!!
					b->bingo = true;
					return *b;
				}
			}
			else
			{
				break;
			}
		}
		// col
		for (int j = 0; j < 5; ++j)
		{
			if (b->plane[j][i] == -1)
			{
				if (j == 4)
				{
					// bingo!!
					b->bingo = true;
					return *b;
				}
			}
			else
			{
				break;
			}
		}
	}
	board bEmpty{};
	return bEmpty;
}

int main ()
{
	// fetch input
	ifstream inpstream("input");
	if (inpstream.is_open())
	{
		string line;
		bool init = true;
		board b{};
		short step;

		while (getline(inpstream, line))
		{
			if (init)
			{
				bingo = split(line, ',');
				init = false;
			}
			else
			{
				if (line == "")
				{
					if (b.init)
					{
						boards.push_back(b);
					}
					step = 0;
					b = board();
					b.init = true;
				}
				else
				{
					vector<int> numbers;
					numbers = splitWS(line);
					for (int i = 0; i < numbers.size(); ++i)
					{
						b.plane[step][i] = numbers[i];
					}
					step++;
				}
			}
		}
	}

	for(char s : bingo)
	{
		for (int l = 0; l < boards.size(); ++l)
		{
			for (int i = 0; i < 5; ++i)
			{
				for (int j = 0; j < 5; ++j)
				{
					board *b = &boards[l];
					char n = b->plane[i][j];
					if (n == s)
					{
						b->plane[i][j] = -1;
						// sqare marked
						// now check for bingo
						board bboard = checkBingo(b);
						if (bboard.bingo)
						{
							int sum = 0;
							cout << "bingooooo!" << endl;
							for (int y = 0; y < 5; ++y)
							{
								cout << endl;
								for (int u = 0; u < 5; ++u)
								{
									int val = (int) bboard.plane[y][u];
									if (val != -1)
									{
										sum += val;
									}
									cout << (int)bboard.plane[y][u] << ' ';
								}
							}

							cout << endl << s << ':' << sum << ' ' << s * sum;
							return 0;
						}
					}
				}
			}
		}
	}

}

