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

struct Node
{
    int x;
    int y;
    int r_cost; // real cost from start
    int h_cost; // heuristic/mh cost to end
    int f_cost; // r + h
};

struct NodeCompare
{
    bool operator()(const Node& a, const Node& b)
    {
        return a.f_cost > b.f_cost;
    }
};

vector<vector<int>> risk_map;
int map_width;
int map_height;

int manhattan_distance(int x1, int y1, int x2, int y2)
{
    return abs(x2 - x1) + abs(y2 - y1);
}

// check if valid
bool is_valid(int x, int y)
{
    return x >= 0 && x < map_width && y >= 0 && y < map_height;
}

// check valid neighbors
vector<Node> get_neighbors(const Node& current)
{
    vector<Node> neighbors;
    int directions[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    
    for (int i = 0; i < 4; i++)
    {
        int new_x = current.x + directions[i][0];
        int new_y = current.y + directions[i][1];
        
        if (is_valid(new_x, new_y))
        {
            neighbors.push_back({new_x, new_y, 0, 0, 0});
        }
    }
    return neighbors;
}

// drijksta
int find_lowest_risk_path()
{
    priority_queue<Node, vector<Node>, NodeCompare> open_list;
    set<pair<int, int>> closed_list;
    map<pair<int, int>, int> r_scores;
    
    int start_x = 0;
    int start_y = 0;
    int goal_x = map_width - 1;
    int goal_y = map_height - 1;
    
    // initialize start node
    Node start_node;
    start_node.x = start_x;
    start_node.y = start_y;
    start_node.r_cost = 0;
    start_node.h_cost = manhattan_distance(start_x, start_y, goal_x, goal_y);
    start_node.f_cost = start_node.r_cost + start_node.h_cost;
    
    open_list.push(start_node);
    r_scores[make_pair(start_x, start_y)] = 0;
    
    while (!open_list.empty())
    {
        Node current = open_list.top();
        open_list.pop();
        
        pair<int, int> current_pos = make_pair(current.x, current.y);
        
        // skip if already processed
        if (closed_list.count(current_pos) > 0)
            continue;
            
        closed_list.insert(current_pos);
        
        #if DEBUG
        printf("Processing node (%d, %d) with f_cost %d\n", current.x, current.y, current.f_cost);
        #endif
        
        // reached goal
        if (current.x == goal_x && current.y == goal_y)
        {
            return current.r_cost;
        }
        
        vector<Node> neighbors = get_neighbors(current);
        for (const auto& neighbor : neighbors)
        {
            pair<int, int> neighbor_pos = make_pair(neighbor.x, neighbor.y);
            
            if (closed_list.count(neighbor_pos) > 0)
                continue;
                
            // FIXED: Get actual cost from risk map
            int tentative_r_cost = current.r_cost + risk_map[neighbor.y][neighbor.x];
            
            bool better_path = false;
            if (r_scores.count(neighbor_pos) == 0)
            {
                better_path = true;
            }
            else if (tentative_r_cost < r_scores[neighbor_pos])
            {
                better_path = true;
            }
            
            if (better_path)
            {
                r_scores[neighbor_pos] = tentative_r_cost;
                
                Node neighbor_node;
                neighbor_node.x = neighbor.x;
                neighbor_node.y = neighbor.y;
                neighbor_node.r_cost = tentative_r_cost;
                neighbor_node.h_cost = manhattan_distance(neighbor.x, neighbor.y, goal_x, goal_y);
                neighbor_node.f_cost = neighbor_node.r_cost + neighbor_node.h_cost;
                
                open_list.push(neighbor_node);
            }
        }
    }
    
    return -1; // no path
}

int main()
{
    vector<string> input = fetch_input("input");
    
    // parse the risk map
    map_height = input.size();
    map_width = input[0].length();
    
    risk_map.resize(map_height);
    for (int y = 0; y < map_height; y++)
    {
        risk_map[y].resize(map_width);
        for (int x = 0; x < map_width; x++)
        {
            risk_map[y][x] = input[y][x] - '0';
        }
    }
    
		#if DEBUG
		printf("Risk map size: %d x %d\n", map_width, map_height);
		for (auto y = 0; y < min(map_height, 10); ++y) {
		    for (auto x = 0; x < min(map_width, 10); ++x) {
		        printf("%d", risk_map[y][x]);
		    }
		    putchar('\n');
		}
		#endif
    
    int lowest_risk = find_lowest_risk_path();
    
    if (lowest_risk != -1)
    {
        printf("Lowest total risk: %d\n", lowest_risk);
    }
    else
    {
        printf("No path found!\n");
    }
    
    return 0;
}