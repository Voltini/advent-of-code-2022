#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <set>
#include <cstring>
#include <queue>
#include <utility>

#define WIDTH 162
#define HEIGHT 41

bool is_valid(int x, int y)
{
    return x - 1 >= 0 && x + 1 < HEIGHT && y - 1 >= 0 && y + 1 < HEIGHT;
}

int propagate(char map[HEIGHT][WIDTH], std::set<std::pair<int, int>> visited, int x, int y)
{
    std::priority_queue<std::pair<int, int>> current_nodes;
    current_nodes.push(std::make_pair(x, y));
    std::priority_queue<std::pair<int, int>> next_nodes;
    int dist(0);
    while (map[x][y] != 'E')
    {
        dist++;
        while (!current_nodes.empty()) {
            std::pair<int, int> point = current_nodes.top();
            if(map[x][y] == 's')
            {
                int a = 0;
            }
            current_nodes.pop();
            if (map[point.first][point.second] == 'E')
            {
                return dist;
            }
            if (point.first >= 1 &&
                (map[point.first - 1][point.second] <= map[point.first][point.second] + 1 || (map[point.first][point.second] == 'z' && map[point.first - 1][point.second] == 'E')) &&
                visited.insert(std::pair<int, int>(point.first - 1, point.second)).second)
            {
                next_nodes.push(std::make_pair(point.first - 1, point.second));
            }
            if (point.second >= 1 &&
                (map[point.first][point.second - 1] <= map[point.first][point.second] + 1 || (map[point.first][point.second] == 'z' && map[point.first][point.second - 1] == 'E')) &&
                visited.insert(std::pair<int, int>(point.first, point.second - 1)).second)
            {
                next_nodes.push(std::make_pair(point.first, point.second - 1));
            }
            if (point.first <= HEIGHT - 2 &&
                (map[point.first + 1][point.second] <= map[point.first][point.second] + 1 || (map[point.first][point.second] == 'z' && map[point.first + 1][point.second] == 'E')) &&
                visited.insert(std::pair<int, int>(point.first + 1, point.second)).second)
            {
                next_nodes.push(std::make_pair(point.first + 1, point.second));
            }
            if (point.second <= WIDTH - 2 &&
                (map[point.first][point.second + 1] <= map[point.first][point.second] + 1 || (map[point.first][point.second] == 'z' && map[point.first][point.second + 1] == 'E')) &&
                visited.insert(std::pair<int, int>(point.first, point.second + 1)).second)
            {
                next_nodes.push(std::make_pair(point.first, point.second + 1));
            }
            x = point.first;
            y = point.second;
        }
        current_nodes = next_nodes;
        next_nodes = std::priority_queue<std::pair<int, int>>();
    }
    return 0;
}

int main() {
    std::ifstream file("input.txt");
    std::set<std::pair<int, int>> visited;
    char map[HEIGHT][WIDTH];
    int i(0);
    std::pair<int, int> start;
    for (std::string line; std::getline(file, line);)
    {
        strcpy(map[i], line.c_str());
        if (map[i][0] == 'S')
        {
            visited.insert(std::pair<int, int>(i, 0));
            map[i][0] = 'a';
        }
        i++;
    }
    std::set<int> dists;
    for (size_t i = 0; i < HEIGHT; i++)
    {
        dists.insert(propagate(map, visited, i, 0));
        visited.clear();
    }
    std::cout << *dists.begin() - 1 << std::endl;
}