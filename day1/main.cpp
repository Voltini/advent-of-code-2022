#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <sstream>

int main() {
    freopen("input.txt", "r", stdin);
    std::ifstream filein("input.txt");

    std::vector<std::vector<int>> input;
    std::vector<int> current_elf;
    std::vector<int> sum;
    int calorie(0);

    for (std::string line; std::getline(filein, line);)
    {
        if(!line.empty()) {
            std::istringstream tmp(line);
            tmp >> calorie;
            current_elf.push_back(calorie);
        } else {
            input.push_back(current_elf);
            current_elf.clear();
        }
    }
    
    for (auto vect : input)
    {
        int result = std::accumulate(vect.begin(), vect.end(), 0);
        sum.push_back(result);
    }
    
    std::sort(sum.begin(), sum.end(), std::greater<int>());

    std::cout << sum[0] + sum[1] + sum[2] << std::endl;

    return 0;
}