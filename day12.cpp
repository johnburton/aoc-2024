#include <optional>
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> load_grid(const std::string &filename)
{
    std::ifstream file("../" + filename);
    std::vector<std::string> grid;
    std::string line;
    while (std::getline(file, line))
    {
        grid.push_back(line);
    }
    return grid;
}

std::optional<std::pair<int, int>> find_non_empty_point(const std::vector<std::string> &grid)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] != '.')
            {
                return std::make_pair(i, j);
            }
        }
    }
    return std::nullopt;
}

// Given a grid and a point, find the size of the shape that contains that point
// Use a recursive algorithm to find the size of the shape, also find the count of borders to the points
// Ensure the grid is left in a state that this will work for the next shape too
// Ensure that borders are only counted once
// Fill in points that are counted with a . after counting them

std::pair<int, int> find_shape_size(std::vector<std::string> &grid, int x, int y, char char_at_point)
{
    if (x < 0 || x >= grid.size() || y < 0 || y >= grid[x].size())
    {
        return std::make_pair(0, 1);
    }
    if (grid[x][y] == '!')
    {
        return std::make_pair(0, 0);
    }
    if (grid[x][y] != char_at_point)
    {
        return std::make_pair(0, 1);
    }
    grid[x][y] = '!';
    auto [area1, border1] = find_shape_size(grid, x + 1, y, char_at_point);
    auto [area2, border2] = find_shape_size(grid, x - 1, y, char_at_point);
    auto [area3, border3] = find_shape_size(grid, x, y + 1, char_at_point);
    auto [area4, border4] = find_shape_size(grid, x, y - 1, char_at_point);
    return std::make_pair(1 + area1 + area2 + area3 + area4, border1 + border2 + border3 + border4);
}

void replace_char(std::vector<std::string> &grid, char from, char to)
{
    for (auto &line : grid)
    {
        for (auto &c : line)
        {
            if (c == from)
            {
                c = to;
            }
        }
    }
}

void print_grid(const std::vector<std::string> &grid)
{
    for (const auto &line : grid)
    {
        std::cout << line << "\n";
    }
    std::cout << "\n";
}

int main()
{
    auto grid = load_grid("day12_test.txt");

    // Scan grid looking for a character that is not a '.'
    // We use '.' to indicate that we have processed that square

    int total = 0;

    while (true)
    {
        auto point_of_interest = find_non_empty_point(grid);
        if (!point_of_interest.has_value())
        {
            break;
        }
        auto [x, y] = point_of_interest.value();
        auto char_at_point = grid[x][y];
        auto [area, border] = find_shape_size(grid, x, y, char_at_point);
        print_grid(grid);
        replace_char(grid, '!', '.');
        std::cout << "Found a shape " << char_at_point << " with area " << area << " and border " << border << "\n";
        total += (area * border);
    }
    std::cout << "Answer is " << total << "\n";
}