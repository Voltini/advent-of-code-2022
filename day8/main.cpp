#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <set>

#define SIZE 99

int area(int i, int j, int forest[][SIZE])
{
    bool up(true), down(true), left(true), right(true);
    int up_see(0), down_see(0), left_see(0), right_see(0);
    int step(0);
    while (up || down || left || right)
    {

        up_see += up;
        down_see += down;
        right_see += right;
        left_see += left; 

        step++;

        up = up && i - step > 0 && forest[i][j] > forest[i - step][j];
        down = down && i + step < SIZE - 1 && forest[i][j] > forest[i + step][j];
        left = left && j - step > 0 && forest[i][j] > forest[i][j - step];
        right = right && j + step < SIZE - 1 && forest[i][j] > forest[i][j + step];
      
        
    }
    return up_see * right_see * down_see * left_see;
}

int main() {
    int visible = 0;
    std::ifstream file("input.txt");
    std::set<std::pair<int, int>> visible_coordinates;
    int heights[SIZE][SIZE];
    int row(0), col(0);
    int max_area(0);
    for(std::string line; std::getline(file, line);)
    {
        col = 0;
        for(char c: line)
        {
            heights[row][col] = c - '0';
            col++;
        }
        row++;
    }

    for (size_t i = 1; i < SIZE - 1; i++)
    {
        int max_left = heights[i][0];
        int max_up = heights[0][i];
        int max_right = heights[i][SIZE - 1];
        int max_down = heights[SIZE - 1][i];

        for (size_t j = 1; j < SIZE - 1; j++)
        {
            if (heights[i][j] > max_left)
            {
                max_left = heights[i][j];                
                visible_coordinates.insert(std::make_pair<int, int>(i, j));
            }
            if (heights[j][i] > max_up)
            {
                max_up = heights[j][i];                
                visible_coordinates.insert(std::make_pair<int, int>(j, i));
            }

            if (heights[i][SIZE - 1 - j] > max_right)
            {
                max_right = heights[i][SIZE - 1 - j];                
                visible_coordinates.insert(std::make_pair<int, int>(i, SIZE - 1 - j));
            }
            if (heights[SIZE - 1 - j][i] > max_down)
            {
                max_down = heights[SIZE - 1 - j][i];                
                visible_coordinates.insert(std::make_pair<int, int>(SIZE - 1 - j, i));
            }
            int current_area = area(i, j, heights);
            if ( current_area > max_area)
            {
                max_area = current_area;
            }
            
        }
    }
    
    //std::cout << visible_coordinates.size() + 4 * (SIZE - 1) << std::endl;
    std::cout << max_area << std::endl;
    return 0;
}