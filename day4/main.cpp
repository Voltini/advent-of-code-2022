#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <tuple>


std::tuple<int, int> get_bounds(std::string interval, char delim)
{
    int start, end;
    size_t pos = interval.find(delim);
    start = std::stoi(interval.substr(0, pos));
    end = std::stoi(interval.substr(pos + 1, interval.size() - 1));
    return std::make_tuple(start, end);
}

int main () {
    std::ifstream filein("input.txt");
    int score(0);
    int total(0);
    for (std::string line; filein >> line;)
    {
        size_t pos = line.find(",");
        auto elf1 = get_bounds(line.substr(0, pos), '-');
        auto elf2 = get_bounds(line.substr(pos + 1, line.size() - 1), '-');
        int start1 = std::get<0>(elf1);
        int end1 = std::get<1>(elf1);
        int start2 = std::get<0>(elf2);
        int end2 = std::get<1>(elf2);
        // part 1
        // if ((start1 <= start2 && end1 >= end2) ||
        // (start2 <= start1 && end2 >= end1))
        // {
        //     score++;
        // }
        // part 2
        if ((end1 < start2 && end2 > start1) ||
        (end2 < start1 && end1 > start2))
        {
            score++;
        }
        total++;
    }
    std::cout << total - score << std::endl;
    return 0;
}