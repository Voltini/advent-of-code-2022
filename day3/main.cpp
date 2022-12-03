#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>

int main () {
    std::ifstream filein("input.txt");
    int score(0);
    for (std::string sack; std::getline(filein, sack);)
    {
        std::cout << sack << "\n";
        std::string first_half(sack.substr(0, sack.size() / 2));
        std::string second_half(sack.substr(sack.size() / 2, sack.size() - 1));
        std::cout << first_half << " " << second_half << "\n";

        std::sort(first_half.begin(), first_half.end());
        std::sort(second_half.begin(), second_half.end());

        std::set<char> outliers;
        std::set_intersection(first_half.begin(),
        first_half.end(),
        second_half.begin(),
        second_half.end(),
        std::inserter(outliers, outliers.begin()));
        std::set<int> a;
        for (char ol : outliers)
        {
            if (isupper(ol))
            {
                score += (ol - 'A' + 27);
            }
            else
            {
                score += (ol - 'a' + 1);
            }
            std::cout << ol;
        }
        std::cout << "\n";
        outliers.clear();
    }
    std::cout << score << std::endl;
    return 0;
}