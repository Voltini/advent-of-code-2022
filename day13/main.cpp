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

enum size { SMALLER, EQUAL, GREATER };

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

size compare_lists(std::shared_ptr<list> l1, std::shared_ptr<list> l2, int index1 = 0, int index2 = 0)
{
    for (size_t i = 0; i < min(l1->elements.size() - index1, l2->elements.size() - index2); i++)
    {
        if (l1->elements[i + index1] != -1 && l2->elements[i + index2] != -1)
        {
            if (l1->elements[i + index1] != l2->elements[i + index2])
            {
                return l1->elements[i + index1] < l2->elements[i + index2] ? SMALLER : GREATER;
            }
        }
        else if (l1->elements[i + index1] == -1 && l2->elements[i + index2] == -1)
        {
            if (l1->lists[i + index1]->elements.empty() && !l2->lists[i + index2]->elements.empty()) return SMALLER;
            if (!l1->lists[i + index1]->elements.empty() && l2->lists[i + index2]->elements.empty()) return GREATER;
            if (l1->lists[i + index1]->elements.empty() && l2->lists[i + index2]->elements.empty()) return EQUAL;
            size below = compare_lists(l1->lists[i], l2->lists[i], index1, index2);
            if (below != EQUAL)
            {
                return below;
            }
        }
        else
        {
            if (l1->elements[i + index1] == -1)
            {
                return compare_lists(l1->lists[i], l2, 0, i);
            }
            else
            {
                return compare_lists(l1, l2->lists[i], i, 0);
            }
        }
        if (i >= l1->elements.size() - 1 && l1->parent != nullptr && l1->parent->parent == nullptr)
        {
            return SMALLER;
        }
    }
    return EQUAL;
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
            size result = compare_lists(l1, l2);
            score += index * (result == SMALLER ? 1 : 0);
            if (result == SMALLER)
            {
                std::cout << index << " ";
            }
        }
    }
    std::cout << "\n";
    std::cout << score << std::endl;
    return 0;
}