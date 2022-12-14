#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <set>
#include <cmath>

int distance(int x1, int y1, int x2, int y2)
{
    return std::max(abs(x1 - x2), abs(y1 - y2));
}

int main() {
    std::ifstream file("input.txt");
    std::set<std::pair<int, int>> visited_coords;
    std::pair<int, int> rope[10] = {std::pair<int, int>(0, 0)};
    visited_coords.insert(rope[9]);
    for(std::string line; std::getline(file, line);)
    {
        std::istringstream line_stream(line);
        char direction;
        int steps;
        line_stream >> direction >> steps;
        int inc_x(0), inc_y(0);
            switch (direction)
            {
                case 'L':
                    inc_x = -1;
                    break;
                case 'R':
                    inc_x = 1;
                    break;
                case 'U':
                    inc_y = 1;
                    break;
                default:
                    inc_y = -1;
                    break;
            }
        for (size_t i = 0; i < steps; i++)
        {
            rope[0].first += inc_x;
            rope[0].second += inc_y;
            for (size_t j = 1; j < 10; j++)
            {       
                if (distance(rope[j - 1].first, rope[j - 1].second, rope[j].first, rope[j].second) >= 2)
                {
                    std::pair<int, int> direction = std::pair<int, int>(rope[j - 1].first - rope[j].first, rope[j - 1].second - rope[j].second);
                    switch (abs(direction.first) + abs(direction.second))
                    {
                    case 3:
                        rope[j].first += direction.first / abs(direction.first);
                        rope[j].second += direction.second / abs(direction.second);
                        break;
                    
                    default:
                        rope[j].first += direction.first != 0 ? direction.first / 2 : 0;
                        rope[j].second += direction.second != 0 ? direction.second / 2: 0;
                        break;
                    }
                    if(j == 9) visited_coords.insert(rope[j]);
                }
            }
        }
    }

    std::cout << visited_coords.size() << std::endl;
    return 0;
}