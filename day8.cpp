#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <set>
#include <iostream>

using namespace std;

struct NodePosition
{
    int x;
    int y;
};

map<char, vector<NodePosition>> read_input(const char* filename, int* width, int* height)
{
    ifstream file(filename);
    map<char, vector<NodePosition>> nodes;

    string line;
    int y = 0;
    int max_width = 0;
    while (getline(file, line))
    {
        int x = 0;
        for (char c : line)
        {
            if (c != '.')
            {
                nodes[c].push_back({x, y});
            }
            x++;
        }
        max_width = max(max_width, x);
        y++;
    }

    *width = max_width;
    *height = y;

    return nodes;
}


int part1()
{
    int width, height;
    auto nodes = read_input("../day8_test.txt", &width, &height);

    std::set<pair<int, int>> antinodes;

    for (auto [c, positions] : nodes)
    {
        // For each pair of positions, calculate the x and y distance
        for (int i = 0; i < positions.size(); i++)
        {
            for (int j = i + 1; j < positions.size(); j++)
            {
                int x_dist = positions[i].x - positions[j].x;
                int y_dist = positions[i].y - positions[j].y;

                std::cout << "Distance: " << x_dist << ", " << y_dist << std::endl;

                int x_first_antinode = positions[i].x + x_dist;
                int y_first_antinode = positions[i].y + y_dist;

                int x_second_antinode = positions[j].x - x_dist;
                int y_second_antinode = positions[j].y - y_dist;

                if (x_first_antinode >= 0 && x_first_antinode < width && y_first_antinode >= 0 && y_first_antinode < height)
                {
                    antinodes.insert({x_first_antinode, y_first_antinode});
                }

                if (x_second_antinode >= 0 && x_second_antinode < width && y_second_antinode >= 0 && y_second_antinode < height)
                {
                    antinodes.insert({x_second_antinode, y_second_antinode});
                }

            }
        }
    }

    // Print how many antinodes there are
    std::cout << "Antinodes: " <<  antinodes.size() << "\n";
}


int part2()
{
    int width, height;
    auto nodes = read_input("../day8.txt", &width, &height);

    std::set<pair<int, int>> antinodes;

    for (auto [c, positions] : nodes)
    {
        // For each pair of positions, calculate the x and y distance
        for (int i = 0; i < positions.size(); i++)
        {
            for (int j = i + 1; j < positions.size(); j++)
            {
                int x_dist = positions[i].x - positions[j].x;
                int y_dist = positions[i].y - positions[j].y;

                std::cout << "Distance: " << x_dist << ", " << y_dist << std::endl;

                int x_first_antinode = positions[i].x;
                int y_first_antinode = positions[i].y;

                int x_second_antinode = positions[j].x;
                int y_second_antinode = positions[j].y;

                while (x_first_antinode >= 0 && x_first_antinode < width && y_first_antinode >= 0 && y_first_antinode < height)
                {
                    antinodes.insert({x_first_antinode, y_first_antinode});
                    x_first_antinode += x_dist;
                    y_first_antinode += y_dist;
                }

                while (x_second_antinode >= 0 && x_second_antinode < width && y_second_antinode >= 0 && y_second_antinode < height)
                {
                    antinodes.insert({x_second_antinode, y_second_antinode});
                    x_second_antinode -= x_dist;
                    y_second_antinode -= y_dist;
                }

            }
        }
    }

    // Print how many antinodes there are
    std::cout << "Antinodes: " <<  antinodes.size() << "\n";
}


int main()
{
    part1();
    part2();

}