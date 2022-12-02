#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <sstream>

int main() {
    std::ifstream filein("input.txt");
    char foe, player;
    const char diff = 'A' - 'X';
    int score = 0;

    for (std::string line; std::getline(filein, line);)
    {
        std::istringstream in(line);
        in >> foe >> player;
        player += diff;
        switch (player)
        {
        case 'A':
            score += 1;
            break;
        case 'B':
            score += 2;
            break;
        default:
            score += 3;
            break;
        }
        if (foe == player)
        {
            score += 3;
        }
        else if ((foe + 1) % 3 == player % 3)
        {
            score += 6;
        }
        std::cout << foe << "\n";
    }
    
    std::cout << score << std::endl;
}