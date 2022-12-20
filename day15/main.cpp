#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cmath>
#include <set>
#include <vector>

typedef struct sensor {
    long long int x;
    long long int y;
    long long int range;
} sensor;

long long int distance(long long int x1, long long int y1, long long int x2, long long int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

std::set<std::pair<long long int, long long int>> generate_perimeter(sensor s)
{
    std::set<std::pair<long long int, long long int>> perimeter;
    const long long int new_range(s.range + 1);
    for (long long int i = -new_range; i <= new_range; i++)
    {
        if (s.x + i >= 0 && s.y + new_range - i >= 0 &&
            s.x + i <= 4e6 && s.y + new_range - i <= 4e6)
        {
            perimeter.insert(std::make_pair(s.x + i, s.y + new_range - i));
        }

        if (s.x + i >= 0 && s.y - new_range + i >= 0 &&
            s.x + i <= 4e6 && s.y - new_range + i <= 4e6)
        {
            perimeter.insert(std::make_pair(s.x + i, s.y - new_range + i));
        }
    }
    return perimeter;

}

int main() {
    std::ifstream file("input.txt");
    std::vector<sensor> all_sensors;
    long long int min_x(1e6), min_y(1e6), max_x(0), max_y(0);
    const long long int LINE_Y = 2000000;
    std::set<std::pair<long long int, long long int>> beacons_on_line;
    long long int scanned(0);
    for (std::string line; std::getline(file, line);)
    {
        std::istringstream line_stream(line);
        sensor s;
        long long int beacon_x, beacon_y;
        line_stream >> s.x >> s.y >> beacon_x >> beacon_y;
        s.range = distance(s.x, s.y, beacon_x, beacon_y);
        all_sensors.push_back(s);
        if (beacon_y == LINE_Y)
        {
            beacons_on_line.insert(std::make_pair(beacon_x, beacon_y));
        }
        if (s.x + s.range > max_x)
        {
            max_x = s.x + s.range;
        }
        if (s.y + s.range > max_y)
        {
            max_y = s.y + s.range;
        }
        if (s.x - s.range < min_x)
        {
            min_x = s.x - s.range;
        }
        if (s.y - s.range < min_y)
        {
            min_y = s.y - s.range;
        }
    }
    // for (long long int i = min_x; i <= max_x; i++)
    // {
    //     for(sensor s: all_sensors)
    //     {
    //         if (distance(s.x, s.y, i, LINE_Y) <= s.range)
    //         {
    //             scanned++;
    //             break;
    //         }
    //     }
    // }
    // 
    // std::cout << scanned - beacons_on_line.size() << std::endl;
    std::set<std::pair<long long int, long long int>> possible_points = generate_perimeter(all_sensors[0]);
    int i = 1;
    while (possible_points.size() > 1)
    {
        std::set<std::pair<long long int, long long int>> current_perimeter = generate_perimeter(all_sensors[i]);
        std::set<std::pair<long long int, long long int>> intersection;
        std::set_intersection(possible_points.begin(), possible_points.end(),
            current_perimeter.begin(), current_perimeter.end(),
            std::inserter(intersection, intersection.begin()));
        possible_points = intersection;
        i++;
    }
    int x = (*possible_points.begin()).first;
    int y = (*possible_points.begin()).second;

    std::cout << std::fixed << (long long int) x * 4e6 + y << std::endl;

    return 0;
}