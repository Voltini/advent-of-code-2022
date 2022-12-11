#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cmath>

long long int upper_lim;

typedef struct monkey
{
    std::vector<long long int> items;
    int id;
    int t_monk;
    int f_monk;
    long long int (*pass)(long long int, long long int);
    long long int op;
    int verif;
    int inspections;
} monkey;

long long int add(long long int a, long long int b)
{
    return (a + b) % upper_lim;
}

long long int mult(long long int a, long long int b)
{
    return (b != 0 ? a * b : a * a) % upper_lim;
}

int main() {
    upper_lim = 1;
    std::ifstream file("input.txt");
    std::vector<monkey> monkeys;
    int ids(0);
    for(std::string line; std::getline(file, line);)
    {
        std::istringstream line_stream(line);
        monkey m;
        m.op = 0;
        m.inspections = 0;
        m.id = ids;
        std::string item;
        int ignored;
        line_stream >> ignored >> item;
        while (item[0] >= '0' && item[0] <= '9')
        {
            m.items.push_back(stoi(item));
            line_stream >> item;
        }
        if (!item.compare("+"))
        {
            m.pass = add;
            line_stream >> m.op;
        }
        if(!item.compare("*"))
        {
            m.pass = mult;
            line_stream >> m.op;
        }
        line_stream >> m.verif >> m.t_monk >> m.f_monk;
        upper_lim *= m.verif;
        monkeys.push_back(m);
        ids++;
    }
    for (size_t j = 0; j < 10000; j++)
    {
        for(int i = 0; i < ids; i++)
        {
            while (!monkeys[i].items.empty())
            {
                int worry = monkeys[i].pass(monkeys[i].items.back(), monkeys[i].op);
                monkeys[i].items.pop_back();
                int target = worry % monkeys[i].verif == 0 ? monkeys[i].t_monk : monkeys[i].f_monk;
                monkeys[target].items.push_back(worry);
                monkeys[i].inspections++;
            }
        }
        
    }
    std::vector<long long int> total_inspections;
    for(monkey m: monkeys)
    {
        total_inspections.push_back(m.inspections);
    }
    std::sort(total_inspections.begin(), total_inspections.end());
    std::cout << total_inspections[ids - 1] * total_inspections[ids - 2] << std::endl;  
    return 0;
}