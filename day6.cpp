#include <set>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>

struct MapContents
{
    std::vector<std::vector<char>> rows;
};

MapContents read_map(const std::string& filename)
{
    MapContents map_contents;

    // Read each line into the map_contents's rows
    std::ifstream input_file(filename);
    std::string line;
    while (std::getline(input_file, line))
    {
        std::vector<char> row;
        for (auto c : line)
        {
            row.push_back(c);
        }
        map_contents.rows.push_back(row);
    }

    return map_contents;
}

struct Position
{
    int x, y;
    int direction; // 0 = up, 1 = right, 2 = down, 3 = left
};

// Find the player in the map, it will be one of the following characters: ^, >, v, <
Position find_position(const MapContents& map_contents)
{
    Position position;
    const std::string directions = "^>v<";
    for (int y = 0; y < map_contents.rows.size(); y++)
    {
        for (int x = 0; x < map_contents.rows[y].size(); x++)
        {
            auto it = directions.find(map_contents.rows[y][x]);
            if (it != std::string::npos)
            {
                position.x = x;
                position.y = y;
                position.direction = it;
                return position;
            }
        }
    }
    return position; // Return a default position if not found
}

int main()
{
    auto map_contents = read_map("../day6.txt");
    auto position = find_position(map_contents);

    // The rules are :-
    //    do the followig steps until you exit the map
    //      check if the next position is not a '#' and if not move forward
    //      if it was a '#' then turn right
    //    
    //    calcaulte the number of distinct positions visited

    std::set<std::pair<int, int>> visited_positions;
    visited_positions.insert({position.x, position.y});

    while (true)
    {
        // Check if the next position is not a '#'
        int next_x = position.x;
        int next_y = position.y;
        switch (position.direction)
        {
            case 0: next_y--; break;
            case 1: next_x++; break;
            case 2: next_y++; break;
            case 3: next_x--; break;
        }

        if (next_y < 0 || next_y >= map_contents.rows.size() || next_x < 0 || next_x >= map_contents.rows[next_y].size())
        {
            break;
        }

        if (map_contents.rows[next_y][next_x] != '#')
        {
            position.x = next_x;
            position.y = next_y;
            visited_positions.insert({position.x, position.y});
        }
        else
        {
            position.direction = (position.direction + 1) % 4;
        }
    }

    std::cout << "Number of distinct positions visited: " << visited_positions.size() << std::endl;
}