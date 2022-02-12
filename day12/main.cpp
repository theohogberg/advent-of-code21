#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

#define DEBUG 0
#include "main.hpp"

struct Cave
{
	string name;
	bool small;
	map<string, Cave*> links;
};

map<string, Cave*> cave_map;

void add_cave (Cave* cave, map<string, Cave*>* cave_map)
{
	int c_count = cave_map->count(cave->name);
	if (c_count == 0)
	{
		(*cave_map)[cave->name] = cave;
	}
}

void set_cave_links (Cave* cave_1, Cave* cave_2)
{
	int c1_count = cave_1->links.count(cave_2->name);
	if (c1_count == 0)
	{
		cave_1->links[cave_2->name] = cave_2;
	}
}

// note: pointer/heap alloc
Cave* get_cave (string cave_str, map<string, Cave*>* cave_map)
{
	Cave* cave;
	if (cave_map->count(cave_str) > 0)
		cave = (*cave_map)[cave_str];
	else
		cave = new Cave{ cave_str, islower(cave_str[0]) != 0, {}};

	return cave;
}

vector<vector<string>> all_paths;
void recursive_search (Cave* cave, vector<string> path)
{
	// add cave to path
	path.push_back(cave->name);

	// path done! push to all paths.
	if (cave->name == "end")
	{
		all_paths.push_back(path);
		return;
	}

	for (const auto& link : cave->links)
	{
		string link_name;
		Cave* link_cave;
		tie(link_name, link_cave) = link;

		// don't go back to start.
		if (link_name == "start")
	    continue;

		bool ok_to_visit = true;
		for (const auto& p : path)
		{
			if (p == link_cave->name && link_cave->small)
			{
				ok_to_visit = false;
				break;
			}
		}

		if (ok_to_visit)
			recursive_search(link_cave, path);
	}	
}

int main ()
{
	vector<string> input = fetch_input("input");
	for (auto& ln_cc : input)
	{
		// printf("%s\n", ln_cc.c_str());
		vector<const char*> cave_split = c_split(ln_cc.c_str(), "-");
		#if DEBUG
		print_vector("cave_split:", cave_split);
		#endif
		string cave_str1 = cave_split[0];
		string cave_str2 = cave_split[1];

		Cave* cave_1 = get_cave(cave_str1, &cave_map);
		Cave* cave_2 = get_cave(cave_str2, &cave_map);

		set_cave_links(cave_1, cave_2);
		set_cave_links(cave_2, cave_1);

		add_cave(cave_1, &cave_map);
		add_cave(cave_2, &cave_map);
	}

	#if DEBUG
	printf("%zd\n", cave_map.size());
	if (cave_map.count("") > 0)
		printf("WARNING: Empty string key in cavemap!\n");
	#endif

	#if DEBUG
	// print caves and their links
	for (const auto& cm_entry : cave_map)
	{
    string name;
    Cave* cave;
		tie(name, cave) = cm_entry;
		printf("links for cave: %s\n", name.c_str());
		for (const auto& link : cave->links)
		{
	    string link_name = link.first;
			printf("\t%s\n", link_name.c_str());
		}
	}
	#endif

	// search the caves!
	Cave* start_cave = cave_map["start"];
	vector<string> path;
	recursive_search(start_cave, path);
	printf("Found %zd paths\n", all_paths.size());

	for (const auto& path : all_paths)
	{
		// print each path.
		for (const auto& p_str : path)
			printf("%s,", p_str.c_str());
		printf("\n");
	}
}
