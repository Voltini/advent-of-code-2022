#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

int main() {
    std::ifstream file("input.txt");
    for (std::string line; std::getline(file, line);)
    {
        std::istringstream line_stream(line);
    }
}