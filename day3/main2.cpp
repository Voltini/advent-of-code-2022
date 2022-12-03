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
    for (std::string sack1; filein >> sack1;)
    {
        std::string sack2;
        std::string sack3;
        filein >> sack2;
        filein >> sack3;

        std::sort(sack1.begin(), sack1.end());
        std::sort(sack2.begin(), sack2.end());
        std::set<char> outliers;
        std::set_intersection(sack1.begin(),
        sack1.end(),
        sack2.begin(),
        sack2.end(),
        std::inserter(outliers, outliers.begin()));

        std::set<char> present_all;

        std::sort(sack3.begin(), sack3.end());

        std::set_intersection(outliers.begin(),
        outliers.end(),
        sack3.begin(),
        sack3.end(),
        std::inserter(present_all, present_all.begin()));

        for (char ol : present_all)
        {
            if (isupper(ol))
            {
                score += (ol - 'A' + 27);
            }
            else
            {
                score += (ol - 'a' + 1);
            }
        }
        outliers.clear();
        present_all.clear();
        sack1.clear();
    }
    std::cout << score << std::endl;
    return 0;
}