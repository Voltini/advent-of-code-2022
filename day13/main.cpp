#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <map>
#include <memory>
#include <stack>
#include <vector>

int min(int a, int b)
{
    return a > b ? b : a;
}

typedef struct list {
    std::vector<int> elements;
    std::map<int, std::shared_ptr<list>> lists;
    std::shared_ptr<list> parent;
} list;

std::shared_ptr<list> list_from_line(std::string line)
{
    std::istringstream line_stream(line);
    std::stack<int> indices;
    int open_brackets(0);
    int index(0);
    std::string in;
    std::shared_ptr<list> current = std::make_shared<list>();
    current->parent = nullptr;
    do
    {
        line_stream >> in;
        if (!in.compare("["))
        {
            open_brackets++;
            current->elements.push_back(-1);
            std::shared_ptr<list> sub_list = std::make_shared<list>();
            sub_list->parent = current;
            current->lists.insert(std::make_pair(index, sub_list));
            current = sub_list;
            indices.push(index);
            index = 0;
        }
        else if (!in.compare("]"))
        {
            open_brackets--;
            current = current->parent;
            index = indices.top();
            index++;
            indices.pop();
        }
        else
        {
            current->elements.push_back(stoi(in));
            index++;
        }
    } while (open_brackets > 0);
    return current;
}

bool compare_lists(std::shared_ptr<list> l1, std::shared_ptr<list> l2)
{
    for (size_t i = 0; i < min(l1->elements.size(), l2->elements.size()); i++)
    {
        if (l1->elements[i] != -1 && l2->elements[i] != -1)
        {
            if (l1->elements[i] != l2->elements[i])
            {
                return l1->elements[i] < l2->elements[i];
            }
        }
        else if(l1->elements[i] == -1 && l2->elements[i] == -1)
        {
            if(l1->lists[i]->elements.empty()) return false;
            if(l2->lists[i]->elements.empty()) return true;
            std::cout << l1->lists[i]->elements[0] << " " <<  l2->lists[i]->elements[0] << "\n";
            return compare_lists(l1->lists[i], l2->lists[i]);
        }
        else
        {
            if (l1->elements[i] == -1)
            {
                return compare_lists(l1->lists[i], l2);
            }
            else
            {
                return compare_lists(l1, l2->lists[i]);
            }
        }
    }
    return l1->elements.size() < l2->elements.size();
}

int main() {
    std::ifstream file("input.txt");
    int score(0), index(0);
    std::shared_ptr<list> l1 = std::make_shared<list>(), l2 = std::make_shared<list>();
    for (std::string line; std::getline(file, line);)
    {
        if (!line.empty())
        {
            l1 = list_from_line(line);
            std::getline(file, line);
            l2 = list_from_line(line);
            index++;
        }
        else
        {
            score += index * compare_lists(l1, l2);
            int a = 0;
        }
    }
    std::cout << score << std::endl;
    return 0;
}