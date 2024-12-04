#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

std::vector<std::string> read_input(const std::string &filename)
{
    std::ifstream file(filename);
    std::vector<std::string> input;
    std::string line;
    while (std::getline(file, line))
    {
        input.push_back(line);
    }
    return input;
}

constexpr auto offsets = std::array{
    std::pair{0, -1}, // UP
    std::pair{1,  1}, // UP-RIGHT
    std::pair{1,  0}, // RIGHT
    std::pair{1, -1}, // DOWN-RIGHT
    std::pair{0,  1}, // DOWN
    std::pair{-1, 1}, // DOWN-LEFT
    std::pair{-1, 0}, // LEFT
    std::pair{-1,-1}  // UP-LEFT
};

// Given a grid consisting of a vector of strings and a coordinate 
// determine how many of the directions indicated by the offsets table above
// form the word "XMAS" starting from the given coordinate.

int count_xmas(const std::vector<std::string> &grid, int x, int y)
{
    int count = 0;
    for (const auto &[dx, dy] : offsets)
    {
        int i = x, j = y;
        std::string word;

        while (i >= 0 && i < grid.size() && j >= 0 && j < grid[i].size())
        {
            word.push_back(grid[i][j]);
            if (word == "XMAS")
            {
                count++;
                break;
            }
            i += dx;
            j += dy;
        }
    }
    return count;
}

bool check_xmas(const std::vector<std::string> &grid, int x, int y)
{
    // Too close to edge
    if (x < 1 || y < 1 || x >= grid[0].size() - 1 || y >= grid.size() - 1)
    {
        return false;
    }

    // If the centre isn't A it can't be right
    if (grid[y][x] != 'A')
    {
        return false;
    }

    char p1 = grid[y - 1][x - 1];  // Top left
    char p2 = grid[y + 1][x - 1];  // Bottom left
    char p3 = grid[y - 1][x + 1];  // Top right
    char p4 = grid[y + 1][x + 1];  // Bottom right

    bool diag_1 = false;
    bool diag_2 = false;

    if ((p1 == 'M' && p4 == 'S') || (p1 == 'S' && p4 == 'M')) diag_1 = true;
    if ((p2 == 'M' && p3 == 'S') || (p2 == 'S' && p3 == 'M')) diag_2 = true;

    return diag_1 && diag_2;
}


int part1()
{
    auto input = read_input("../day4.txt");
    int count = 0;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            count += count_xmas(input, i, j);
        }
    }
    return count;
}

int part2()
{
    auto input = read_input("../day4.txt");
    int count = 0;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            count += check_xmas(input, i, j);
        }
    }
    return count;
}

int main()
{
    std::cout << part1() << std::endl;
    std::cout << part2() << std::endl;
}