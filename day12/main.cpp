#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <set>
#include <cstring>

#define WIDTH 9
#define HEIGHT 5

int propagate(char map[HEIGHT][WIDTH], std::set<std::pair<int, int>> visited, int x, int y)
{
    if (map[x][y] == 'E')
    {
        return 0;
    }
    
    int neighbours[4] = {HEIGHT * WIDTH + 1,
    HEIGHT * WIDTH + 1,
    HEIGHT * WIDTH + 1,
    HEIGHT * WIDTH + 1};
    if(x >= 1 && 
    (map[x - 1][y] == map[x][y] || map[x - 1][y] == map[x][y] + 1 || map[x - 1][y] == map[x][y] + 1) &&
    visited.insert(std::pair<int, int>(x - 1, y)).second)
    {
        neighbours[0] = 1 + propagate(map, visited, x - 1, y);
    }
    if(y >= 1 &&
    (map[x][y - 1] == map[x][y] || map[x][y - 1] == map[x][y] + 1 || map[x][y - 1] == map[x][y] + 1) &&
    visited.insert(std::pair<int, int>(x, y - 1)).second)
    {
        neighbours[1] = 1 + propagate(map, visited, x, y - 1);
    }
    if(x <= WIDTH - 2 &&
    (map[x + 1][y] == map[x][y] || map[x + 1][y] == map[x][y] + 1 || map[x + 1][y] == map[x][y] + 1) &&
    visited.insert(std::pair<int, int>(x + 1, y)).second)
    {
        neighbours[2] = 1 + propagate(map, visited, x + 1, y);
    }
    if (y <= HEIGHT - 2 &&
    (map[x][y + 1] == map[x][y] || map[x][y + 1] == map[x][y] + 1 || map[x][y + 1] == map[x][y] + 1) &&
    visited.insert(std::pair<int, int>(x, y + 1)).second)
    {
        neighbours[3] = 1 + propagate(map, visited, x, y + 1);
    }
    int min = neighbours[0];
    for (size_t i = 1; i < 4; i++)
    {
        if(min > neighbours[i]) min = neighbours[i];
    }
    return min;
}

int main() {
    std::ifstream file("input.txt");
    std::set<std::pair<int, int>> visited;
    char map[HEIGHT][WIDTH];
    int i(0);
    std::pair<int, int> start;
    for(std::string line; std::getline(file, line);)
    {
        strcpy(map[i], line.c_str());
        if (map[i][0] == 'S')
        {
            visited.insert(std::pair<int, int>(i, 0));
            map[i][0] = 'a';
        }
        i++;
    }
    std::cout << propagate(map, visited, (*visited.begin()).first, (*visited.begin()).second) << std::endl;
}