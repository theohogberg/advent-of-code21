#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

#define DEBUG 0
#include "main.hpp"

struct Point
{
	int x;
	int y;
};
struct Paper
{
	set<pair<int, int>> dots;
	int width;
	int height;
};
struct Fold
{
	char axis;
	int value;
};

// add point to paper
void add_dot(Paper* paper, Point* point)
{
	pair<int, int> p(point->x, point->y);
	paper->dots.insert(p);
	paper->width = max(paper->width, point->x + 1);
	paper->height = max(paper->height, point->y + 1);
}

// note: put in stack. no desc?
Point* get_point(string point_str)
{
	vector<string> coord_split = cpp_split(point_str, ",");
	
	int x = stoi(coord_split[0]);
	int y = stoi(coord_split[1]);
	
	return new Point{ x, y };
}

// fold instruction
Fold* get_fold(string fold_str)
{
	// format: fold along x=123
	vector<string> parts = cpp_split(fold_str, " ");
	string axis_part = parts[parts.size() - 1];
	vector<string> fold_split = cpp_split(axis_part, "=");

	char axis = fold_split[0][0];
	int value = stoi(fold_split[1]);

	return new Fold{ axis, value };
}

// do fold
void fold_paper(Paper* paper, Fold* fold)
{
	set<pair<int, int>> new_dots;
	
	for (const auto& dot : paper->dots)
	{
		int x = dot.first;
		int y = dot.second;
		
		if (fold->axis == 'x' && x > fold->value)
		{ // fold left
			x = 2 * fold->value - x;
		}
		else if (fold->axis == 'y' && y > fold->value)
		{ // fold up
			y = 2 * fold->value - y;
		}
		
		new_dots.insert(make_pair(x, y));
	}
	
	paper->dots = new_dots;
	
	// update dimensions
	if (fold->axis == 'x')
		paper->width = fold->value;
	else if (fold->axis == 'y')
		paper->height = fold->value;
}

// print paper
void print_paper(Paper* paper)
{
	for (int y = 0; y < paper->height; y++)
	{
		for (int x = 0; x < paper->width; x++)
		{
			pair<int, int> p(x, y);
			if (paper->dots.count(p) > 0)
				printf("#");
			else
				printf(".");
		}
		printf("\n");
	}
}

int main ()
{
	vector<string> input = fetch_input("input");
	Paper* paper = new Paper{ {}, 0, 0 };
	vector<Fold*> folds;
	
	// parse input
	bool parsing_dots = true;
	for (auto& in_ln : input)
	{
		if (in_ln.empty())
		{
			parsing_dots = false;
			continue;
		}
		
		if (parsing_dots)
		{
			Point* point = get_point(in_ln);
			add_dot(paper, point);
		}
		else
		{
			Fold* fold = get_fold(in_ln);
			folds.push_back(fold);
		}
	}
	
	#if DEBUG
	printf("Initial paper: %d x %d with %zd dots\n", paper->width, paper->height, paper->dots.size());
	for (const auto& fold : folds)
	{
		printf("Fold along %c=%d\n", fold->axis, fold->value);
	}
	#endif
	
	// part 1. only first fold
	fold_paper(paper, folds[0]);
	printf("After first fold: %zd dots\n", paper->dots.size());
	
	// part 2. do all folds
	for (size_t i = 1; i < folds.size(); i++)
	{
		fold_paper(paper, folds[i]);
	}
	
	printf("Final paper after %zd folds:\n", folds.size());
	print_paper(paper);
	
	return 0;
}