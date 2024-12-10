#include <fstream>
#include <string>
#include <set>
#include <tuple>
#include <vector>
#include <iostream>

struct Position
{
    int x;
    int y;
};

bool operator<(const Position &lhs, const Position &rhs)
{
    return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}

// Read a square grid of numbers into a vector of strings
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

// Get positions of all of the '0' characters (starting_points)
std::vector<Position> get_starting_points(const std::vector<std::string> &input)
{
    std::vector<Position> starting_points;
    for (int i = 0; i < input.size(); i++)
    {
        for (int j = 0; j < input[i].size(); j++)
        {
            if (input[i][j] == '0')
            {
                starting_points.push_back({i, j});
            }
        }
    }
    return starting_points;
}

void print(const std::vector<Position> &starting_points)
{
    for (const auto &point : starting_points)
    {
        std::cout << "(" << point.x << "," << point.y << ") " ;
    }
    std::cout << "\n";
}

// Find all the routes through increasing numbers until we reach a 9
// in which case record the position in end_points, or until we don't
// have any valid moves or we fall off the map

void find_routes(const std::vector<std::string> &input, const Position &start, char next, std::set<Position> &end_points)
{
    if (start.x < 0 || start.x >= input.size() || start.y < 0 || start.y >= input[start.x].size())
    {
        return;
    }

    if (input[start.x][start.y] != next)
    {
        return;
    }

    if (next == '9')
    {
        end_points.insert(start);
        return;
    }

    // Try all possible directions recursively
    find_routes(input, {start.x + 1, start.y}, next + 1, end_points);
    find_routes(input, {start.x - 1, start.y}, next + 1, end_points);
    find_routes(input, {start.x, start.y + 1}, next + 1, end_points);
    find_routes(input, {start.x, start.y - 1}, next + 1, end_points);
}

void find_routes1(const std::vector<std::string> &input, const Position &start, char next, std::vector<Position> &end_points)
{
    if (start.x < 0 || start.x >= input.size() || start.y < 0 || start.y >= input[start.x].size())
    {
        return;
    }

    if (input[start.x][start.y] != next)
    {
        return;
    }

    if (next == '9')
    {
        end_points.push_back(start);
        return;
    }

    // Try all possible directions recursively
    find_routes1(input, {start.x + 1, start.y}, next + 1, end_points);
    find_routes1(input, {start.x - 1, start.y}, next + 1, end_points);
    find_routes1(input, {start.x, start.y + 1}, next + 1, end_points);
    find_routes1(input, {start.x, start.y - 1}, next + 1, end_points);
}

void part1()
{
    auto input = read_input("../day10.txt");
    auto starting_points = get_starting_points(input);

    int endpoint_count = 0;
    for (auto &point : starting_points)
    {
        std::set<Position> end_points;
        find_routes(input, point, '0', end_points);
        endpoint_count += end_points.size();
    }

    std::cout << "Total: " << endpoint_count << "\n";
}

void part2()
{
    auto input = read_input("../day10.txt");
    auto starting_points = get_starting_points(input);

    int endpoint_count = 0;
    for (auto &point : starting_points)
    {
        std::vector<Position> end_points;
        find_routes1(input, point, '0', end_points);
        endpoint_count += end_points.size();
    }

    std::cout << "Total: " << endpoint_count << "\n";
}

int main()
{
    part1();
    part2();
}