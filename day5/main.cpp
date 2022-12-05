#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>
#include <vector>

std::vector<std::stack<char>> fill_stack()
{
    std::ifstream inputs("formatted.txt");
    std::vector<std::stack<char>> result;
    for(std::string line; inputs >> line;)
    {
        std::stack<char> current;
        for(int i = line.size() - 1; i >= 0; i--)
        {
            current.push(line[i]);
        }
        result.push_back(current);
    }
    return result;
}

int main () {
    std::ifstream filein("input.txt");
    std::vector<std::stack<char>> containers = fill_stack();

    for(std::string line; std::getline(filein, line);)
    {
        int to_move, from, to;
        std::istringstream in_stream(line);
        in_stream >> to_move >> from >> to;
        std::stack<char> gru;
        for (size_t i = 0; i < to_move; i++)
        {
            gru.push(containers[from - 1].top());
            containers[from - 1].pop();
        }
        while (!gru.empty())
        {
            containers[to - 1].push(gru.top());
            gru.pop();
        }
        
    }
    for (size_t i = 0; i < containers.size(); i++)
    {
        std::cout << containers[i].top();
    }
    std::cout << std::endl;
    return 0;
}