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
    std::pair<int, int> head(0, 0), tail(0,0);
    visited_coords.insert(tail);
    for(std::string line; std::getline(file, line);)
    {
        std::istringstream line_stream(line);
        char direction;
        int steps;
        line_stream >> direction >> steps;
        for (size_t i = 0; i < steps; i++)
        {
            int inc_x(0), inc_y(0);
            std::pair<int, int> old_pos = head;
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
            head.first += inc_x;
            head.second += inc_y;
            if (distance(head.first, head.second, tail.first, tail.second) >= 2)
            {
                tail = old_pos;
                visited_coords.insert(tail);
            }
            
        }
    }

    
    
    //std::cout << visible_coordinates.size() + 4 * (SIZE - 1) << std::endl;
    std::cout << visited_coords.size() << std::endl;
    return 0;
}