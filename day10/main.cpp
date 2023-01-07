#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>

void verify_signal(int &step, int &secret, int strength, bool screen[6][40])
{
    if (strength == (step % 40) || strength == (step % 40) + 1 || strength == (step % 40) - 1)
    {
        screen[step / 40][step % 40] = true;
    }
    step++;
    if (step % 40 == 20)
    {
        secret += strength * step;
    }
    
    
    
}

int main()
{
    std::ifstream file("input.txt");
    int strength(1);
    int secret(0);
    int step(1);
    bool screen[6][40] = {false, false, false, false, false, false};

    for (std::string line; std::getline(file, line);)
    {
        std::istringstream line_stream(line);
        std::string command;
        line_stream >> command;
        verify_signal(step, secret, strength, screen);
        if (command.compare("noop"))
        {
            int inc;
            line_stream >> inc;
            strength += inc;
            verify_signal(step, secret, strength, screen);
        }

    }
    std::cout << secret << "\n";

    for (size_t i = 0; i < 6; i++)
    {
        for (size_t j = 0; j < 40; j++)
        {
            std::cout << (screen[i][j] ? '#' : '.');
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
    
    return 0;
}