#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#define DEBUG 0
#include "main.hpp"

char open_chunk[4] = { '(', '[', '{', '<' };
char close_chunk[4] = { ')', ']', '}', '>' };

// put in each stack
vector<char> open_stack;
vector<char> corrupt_stack;
vector<char> score_stack;

short char_index (char ch, char* chunk)
{
	for (short x = 0; x < 4; x++)
	{
		short c = chunk[x];
		if (c == ch)
		{
			return x;
		}
	}
	return -1;
}

void check_stack (char ch, vector<char>* stack)
{
	char last_ch = (*stack)[stack->size() - 1];

	short ch_i = char_index(ch, close_chunk);
	short last_ch_i = char_index(last_ch, open_chunk);
	
	// debug
	#if DEBUG
	printf("%c, %c\n", ch, last_ch);
	printf("%hd, %hd\n", ch_i, last_ch_i);
	#endif

	if (ch_i == last_ch_i)
	{ // pop the stack
		stack->pop_back();
	}
	else
	{ // corrupt stack
		corrupt_stack.push_back(ch);
	}
}

int main ()
{
	vector<string> input = fetch_input("input");
	// printf("%p\n", &input);
	for (auto& ln : input)
	{
		// debug
		#if DEBUG
		printf("%s\n", ln.c_str());
		#endif

		// check line corrupted
		for (auto& ch : ln)
		{
			char close_char = char_index(ch, close_chunk);
			if (close_char == -1)
			{ // not close char add it to the open_stack
				open_stack.push_back(ch);
			}
			else
			{ // closed char; check open_stack for maches
				// printf("closed: %c\n", ch);
				check_stack(ch, &open_stack);
			}
		}
		
		// debug
		#if DEBUG
		print_vector("open stack: ", open_stack);
		print_vector("corrupt stack: ", corrupt_stack);
		#endif

		if (!corrupt_stack.empty())
		{
			score_stack.push_back(corrupt_stack[0]);
		}
		corrupt_stack.clear();
	}

	// debug
	print_vector("score stack: ", score_stack);

	uint score = 0;
	for (auto& c: score_stack)
	{
		if (c == ')') score += 3;
		else if (c == ']') score += 57;
		else if (c == '}') score += 1197;
		else if (c == '>') score += 25137;
	}

	printf("%u\n", score);
}
