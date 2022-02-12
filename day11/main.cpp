#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

#define DEBUG 0
#include "main.hpp"

struct Octopus {
	int y;
	int x;
};

int octopuses[10][10];
vector<Octopus> octos_to_flash;
vector<Octopus> octos_to_reset;
uint flashes = 0;

void print_octos (int octos[][10])
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
			cout << setw(2) << octos[y][x] << ' ';
		cout << endl;
	}
	cout << endl;	
}

void print_octos_compact (int octos[][10])
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
			cout << octopuses[y][x];
		cout << endl;
	}
	cout << endl;	
}

// THE way to refer to 2d arrays. f-ing internet.
void power_up (int octos[][10])
{
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			octos[y][x]++;
		}
	}
}

void check_octos (int octos[][10], vector<Octopus>* otl)
{
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
		{
			if (octos[y][x] > 9)
			{
				Octopus op = {y, x};
				otl->push_back(op);
			}
		}
}

void flash_octos (int octos[][10], vector<Octopus>* otl)
{
	for (auto& octo : (*otl))
	{
		int y = octo.y; int x = octo.x;

		// 1 2 3
		// 4 x 5
		// 6 7 8
		if (x > 0)
		{
			octos[y][x-1]++; //4
			if (y > 0)
			{
				octos[y-1][x-1]++; //1
			}
		}

		if (y > 0)
		{
			octos[y-1][x]++; //2
			if (x < 9)
			{
				octos[y-1][x+1]++; //3
			}
		}

		if (x < 9)
		{
			octos[y][x+1]++; //5
			if (y < 9)
			{
				octos[y+1][x+1]++; //8
			}
		}

		if (y < 9)
		{
			octos[y+1][x]++; //7
			if (x > 0)
			{
				octos[y+1][x-1]++; //6
			}
		}

		flashes++;
	}
}

void reset_octos (int octos[][10], vector<Octopus>* otl)
{
	for (auto& octo : (*otl))
	{
		octos[octo.y][octo.x] = 0;
	}
}

int main ()
{
	vector<string> input = fetch_input("input");
	// print_vector("input: ", input);

	// load octos and print them
	cout << endl <<"loaded octos:" << endl;
	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			octopuses[y][x] = input[y][x] - '0';
			cout <<  octopuses[y][x];
		}
		cout << endl;		
	}
	cout << endl;		

	uint step = 1;
	// 1. increase the energy.
	octo_begin:
	#if DEBUG
	printf("step %d octos:\n", step);
	print_octos(octopuses);
	#endif

	power_up(octopuses);
	#if DEBUG
	printf("powered octos:\n");	
	print_octos(octopuses);
	#endif

	// 2a. check which octos should be lit.
	check_octos(octopuses, &octos_to_flash);

	// 2b. flash the octos!
	octo_flsh:
	flash_octos(octopuses, &octos_to_flash);
	#if DEBUG	
	printf("flashed octos:\n");
	print_octos(octopuses);
	#endif
		
	// 2c. umm..
	for (auto& octo_p : octos_to_flash)
	{
		octos_to_reset.push_back(octo_p);
	}
	reset_octos(octopuses, &octos_to_reset);
	octos_to_flash.clear();

	// 2d. if there are new octos then go back.
	check_octos(octopuses, &octos_to_flash);
	if (!octos_to_flash.empty())
	{
		goto octo_flsh;
	}
	// 3. reset flashed octos.
	else
	{
		reset_octos(octopuses, &octos_to_reset);
		octos_to_reset.clear();
	}
	// step done!
	printf("step %d done!\n", step);	
	print_octos_compact(octopuses);

	step++;
	if (step <= 100)
	{
		goto octo_begin;
	}

	cout << "total flashes: " << flashes << endl;
}
