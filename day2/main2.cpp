#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <sstream>

int main() {
    std::ifstream filein("input.txt");
    char foe, outcome;
    char play;
    int score = 0;

    for (std::string line; std::getline(filein, line);)
    {
        std::istringstream in(line);
        in >> foe >> outcome;
        switch (outcome)
        {
        case 'X':
            play = ((foe + 4) % 'C') % 3 + 'A';
            break;
        case 'Y':
            play = foe;
            score += 3;
            break;
        default:
            play = ((foe + 1) % 'A') % 3 + 'A';
            score += 6;
            break;
        }
        switch (play)
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
    }
    
    std::cout << score << std::endl;
}