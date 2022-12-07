#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>
#include <set>
#include <memory>

typedef struct tree {
    std::string name;
    std::unordered_map<std::string, std::shared_ptr<tree>> elements;
    std::shared_ptr<tree> parent;
    int size;
} tree;


int count_size(std::shared_ptr<tree> root)
{
    if (root->elements.empty())
    {
        return root->size;
    }
    for (auto& [name, elt] : root->elements)
    {
        root->size += count_size(elt);
    }
    return root->size;
}

long long int total(std::shared_ptr<tree> root)
{
    if (root->elements.empty())
    {
        return root->size <= 1e5 ? root->size : 0;
    }

    long long int result = root->size <= 1e5 ? root->size : 0;
    for (auto& [name, elt] : root->elements)
    {
        if (!elt->elements.empty()) { result += total(elt); }
    }
    return result;
}

int to_delete(std::shared_ptr<tree> root, int goal)
{
    int dirs = 0;
    int unviable_dirs = 0;
    std::shared_ptr<tree> viable_min = root;
    std::set<int> viable_sizes;
    for(auto& [name, elt]: root->elements)
    {
        if(!elt->elements.empty()) dirs++;
        if(!elt->elements.empty() && elt->size < goal) unviable_dirs++;
        else
        {
            if(!elt->elements.empty() && elt->size > goal)
            {
                viable_min = elt;
                viable_sizes.insert(to_delete(viable_min, goal));
            }
        }
    }
    if (unviable_dirs == dirs)
    {
        return root->size;
    }
    return *viable_sizes.begin();
} 

int main() {
    std::ifstream filein("input.txt");
    bool is_command = false;
    bool listing = false;
    char $;
    std::string command, options;
    std::string cwd;
    std::shared_ptr<tree> filesystem = std::make_shared<tree>();
    std::vector<tree> empty;
    filesystem->name = std::string("/");
    filesystem->size = 0;
    filesystem->parent = nullptr;
    for (std::string line; std::getline(filein, line);)
    {
        std::istringstream line_stream(line);
        if (line[0] == '$')
        {
            is_command = true;
            listing = false;
        }

        if (listing)
        {
            std::string type, name;
            line_stream >> type >> name;
            int size(0);
            std::shared_ptr<tree> element = std::make_shared<tree>();
            element->name = name;
            element->parent = filesystem;
            if (type.compare("dir"))
            {
                size = std::stoi(type);
            }
            element->size = size;
            filesystem->elements.insert(std::pair<std::string, std::shared_ptr<tree>>(name, element));
        }

        if (is_command)
        {
            line_stream >> $ >> command >> options;
            if (!command.compare("ls"))
            {
                is_command = false;
                listing = true;
            }
            else if (!command.compare("cd"))
            {
                if (options.compare("/"))
                {
                    if (!options.compare(".."))
                    {
                        filesystem = filesystem->parent;
                    }
                    else
                    {
                        filesystem = filesystem->elements[options];
                    }
                }
            }
        }
    }
    while (filesystem->parent)
    {
        filesystem = filesystem->parent;
    }

    count_size(filesystem);

    //std::cout << total(filesystem) << std::endl;
    std::cout << to_delete(filesystem, filesystem->size - 4e7) << std::endl;

    return 0;
}