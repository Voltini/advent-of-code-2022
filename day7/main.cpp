#include <unordered_map>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
#include <stack>

int count_size(std::string root, std::unordered_map<std::string, std::vector<std::string>> tree, std::unordered_map<std::string, int>* sizes)
{
    if (tree.find(root) == tree.end())
    {
        return (*sizes)[root];
    }
    for (std::string elt : tree[root])
    {
        (*sizes)[root] += count_size(elt, tree, sizes);
    }
    return (*sizes)[root];
}

int main() {
    std::ifstream filein("input.txt");
    bool is_command = false;
    bool listing = false;
    char $;
    std::string command, options;
    std::string cwd;
    std::unordered_map<std::string, std::vector<std::string>> tree;
    std::unordered_map<std::string, int> sizes;
    std::stack<std::string> path;
    std::string slash("/");
    std::vector<std::string> empty;
    tree.insert(std::pair<std::string, std::vector<std::string>>(slash, empty));
    sizes.insert(std::pair<std::string, int>("/", 0));
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
            tree[cwd].push_back(name);
            if (!type.compare("dir"))
            {
                std::vector<std::string> dir_elts;
                tree.insert(std::pair<std::string, std::vector<std::string>>(name, dir_elts));
            }
            else {
                size = std::stoi(type);
            }
            sizes.insert(std::pair<std::string, int>(name, size));
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
                if (options.compare(".."))
                {
                    path.push(options);
                    cwd = options;
                }
                else
                {
                    path.pop();
                    cwd = path.top();
                }

            }
        }
    }
    count_size(std::string("/"), tree, &sizes);
    int result = 0;
    for(auto& [elt, size]: sizes)
    {
        if(tree.find(elt) != tree.end() && sizes[elt] <= 1e5)
        {
            result += size;
        }
    }

    std::cout << result << std::endl;
    return 0;
}