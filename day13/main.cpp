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

size compare_lists(std::shared_ptr<list> l1, std::shared_ptr<list> l2)
{
    if (l1->elements.empty() && !l2->elements.empty())
    {
        return SMALLER;
    }
    if (l2->elements.empty() && !l1->elements.empty())
    {
        return GREATER;
    }
    for (size_t i = 0; i < min(l1->elements.size(), l2->elements.size()); i++)
    {
        if (l1->elements[i] != -1 && l2->elements[i] != -1)
        {
            if (l1->elements[i] != l2->elements[i])
            {
                return l1->elements[i] < l2->elements[i] ? SMALLER : GREATER;
            }
        }
        else if (l1->elements[i] == -1 && l2->elements[i] == -1)
        {
            //if (l1->lists[i]->elements.empty() && !l2->lists[i]->elements.empty()) return SMALLER;
            //if (!l1->lists[i]->elements.empty() && l2->lists[i]->elements.empty()) return GREATER;
            //if (l1->lists[i]->elements.empty() && l2->lists[i]->elements.empty()) return EQUAL;
            size below = compare_lists(l1->lists[i], l2->lists[i]);
            if (below != EQUAL)
            {
                return below;
            }
        }
        else
        {
            std::shared_ptr<list> list_1_elem = std::make_shared<list>();
            if (l1->elements[i] == -1)
            {
                list_1_elem->elements.push_back(l2->elements[i]);
                list_1_elem->parent = l1;
                return compare_lists(l1->lists[i], list_1_elem);
            }
            else
            {
                list_1_elem->elements.push_back(l1->elements[i]);
                list_1_elem->parent = l1;
                size below = compare_lists(list_1_elem, l2->lists[i]);
                if (below != EQUAL)
                {
                    return below;
                }
            }
        }
        if (i >= l1->elements.size() - 1 && i < l2->elements.size() - 1)
        {
            return SMALLER;
        }
        else if (i >= l2->elements.size() - 1 && i < l1->elements.size() - 1)
        {
            return GREATER;
        }
    }
    return EQUAL;
}

int main() {
    std::ifstream file("input.txt");
    int score(1), index(0);
    std::shared_ptr<list> l1 = std::make_shared<list>();
    std::shared_ptr<list> l2 = std::make_shared<list>();
    std::vector<std::shared_ptr<list>> all_lists;
    std::vector<std::shared_ptr<list>> sorted_lists;

    for (std::string line; std::getline(file, line);)
    {
        // if (!line.empty())
        // {
        //     l1 = list_from_line(line);
        //     std::getline(file, line);
        //     l2 = list_from_line(line);
        //     index++;
        // }
        // else
        // {
        //     if (index == 74)
        //     {
        //         int a = 0;
        //     }

        //     size result = compare_lists(l1, l2);
        //     score += index * (result == SMALLER ? 1 : 0);
        //     if (result == SMALLER)
        //     {
        //         std::cout << index << " ";
        //     }
        // }
        all_lists.push_back(list_from_line(line));
    }

    while (!all_lists.empty())
    {
        std::shared_ptr<list> min = all_lists[0];
        int min_i = 0;
        for (size_t j = 1; j < all_lists.size(); j++)
        {
            if (compare_lists(all_lists[j], min) != GREATER)
            {
                min = all_lists[j];
                min_i = j;
            }
        }
        all_lists.erase(all_lists.begin() + min_i);
        sorted_lists.push_back(min);
    }
    for (size_t i = 0; i < sorted_lists.size(); i++)
    {
        if (sorted_lists[i]->lists.size() == 1 &&
            sorted_lists[i]->lists[0]->lists.size() == 1 &&
            sorted_lists[i]->lists[0]->lists.find(0) != sorted_lists[i]->lists[0]->lists.end() &&
            sorted_lists[i]->lists[0]->lists[0]->elements.size() == 1 &&
            (sorted_lists[i]->lists[0]->lists[0]->elements[0] == 2 || sorted_lists[i]->lists[0]->lists[0]->elements[0] == 6))
        {
            score *= (i + 1);
        }

    }


    std::cout << "\n";
    std::cout << score << std::endl;
    return 0;
}