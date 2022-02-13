#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>

using namespace std;

#define DEBUG 0
#include "main.hpp"

struct Rule
{
	string pair;
	string insert;
};

struct Polymer
{
	string template_str;
	map<string, long long> pair_counts;
	map<char, long long> char_counts;
	map<string, string> rules;
};

// initialize polymer from template
void init_polymer (Polymer* polymer, string template_str)
{
	polymer->template_str = template_str;
	
	// initialize character counts
	for (char c : template_str)
	{
		polymer->char_counts[c]++;
	}
	
	// initialize pair counts
	for (size_t i = 0; i < template_str.length() - 1; i++)
	{
		string pair = template_str.substr(i, 2);
		polymer->pair_counts[pair]++;
		#if DEBUG
		printf("init pair count %s: %llu\n", pair.c_str(), polymer->pair_counts[pair]);
		#endif		
	}
}

// get rule from string
Rule* get_rule (string rule_str)
{
	vector<string> rule_split = cpp_split(rule_str, " -> ");
	
	string pair = rule_split[0];
	string insert = rule_split[1];
	
	return new Rule{ pair, insert };
}

// process one step of polymer growth
void grow_polymer (Polymer* polymer)
{
	map<string, long long> new_pairs;
	
	// for each existing pair
	for (const auto& pair_entry : polymer->pair_counts)
	{
		string pair = pair_entry.first;
		long long count = pair_entry.second;
		
		// check if we have a rule for this pair
		if (polymer->rules.count(pair) > 0)
		{
			string insert = polymer->rules[pair];
			char insert_char = insert[0];
			
			// create new pairs: AB -> A(insert)B => A(insert) and (insert)B
			string pair1 = pair[0] + insert;
			string pair2 = insert + pair[1];
			
			// add new pairs
			new_pairs[pair1] += count;
			new_pairs[pair2] += count;
			
			// update char counts
			polymer->char_counts[insert_char] += count;
		}
		else
		{
			// if no rule, keep the pair
			new_pairs[pair] += count;
		}
	}
	
	// update pair counts
	polymer->pair_counts = new_pairs;
}

// get result (most common - least common character count)
long long get_result (Polymer* polymer)
{
	long long max_count = 0;
	long long min_count = LLONG_MAX;
	
	for (const auto& char_entry : polymer->char_counts)
	{
		long long count = char_entry.second;
		max_count = max(max_count, count);
		min_count = min(min_count, count);
	}
	
	return max_count - min_count;
}

int main ()
{
	vector<string> input = fetch_input("input");
	Polymer p = Polymer{ "", {}, {}, {} };
	Polymer* polymer = &p;
	
	// parse input
	string template_str = input[0];
	init_polymer(polymer, template_str);
	
	// skip empty line and parse rules
	for (size_t i = 2; i < input.size(); i++)
	{
		Rule* rule = get_rule(input[i]);
		polymer->rules[rule->pair] = rule->insert;
	}
	
	#if DEBUG
	printf("template: %s\n", polymer->template_str.c_str());
	printf("rules count: %zd\n", polymer->rules.size());
	printf("initial pairs: \n");
	for (const auto& pair_entry : polymer->pair_counts)
	{
		printf("%s: %lld\n", pair_entry.first.c_str(), pair_entry.second);
	}
	#endif
	
	// part 1. 10 steps
	for (int step = 0; step < 10; step++)
	{
		grow_polymer(polymer);
	}
	printf("after 10 steps: %lld\n", get_result(polymer));
	
	// part 2. 30 more steps (40 total)
	for (int step = 0; step < 30; step++)
	{
		grow_polymer(polymer);
	}
	printf("after 40 steps: %lld\n", get_result(polymer));
	
	return 0;
}