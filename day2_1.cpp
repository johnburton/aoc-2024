#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <climits>

// The input consists of a list of integers separated by spaces.
// There are many lines of integers, each line is a vector of integers.
std::vector<std::vector<int>> read_input(const std::string& file_name)
{
    std::ifstream input_file{file_name};

    std::vector<std::vector<int>> columns;

    std::vector<int> column;
    int value;
    while(input_file >> value)
    {
        column.push_back(value);
        if (input_file.peek() == '\n')
        {
            columns.push_back(column);
            column.clear();
        }
    }

    return columns;
}

bool is_row_valid(const std::vector<int>& row)
{
    int old_value = 0;
    bool is_increasing = true;
    bool is_decreasing = true;
    bool is_valid = true;
    bool is_first = true;

    for (auto value: row)
    {
        if (is_first)
        {
            old_value = value;
            is_first = false;
            continue;
        }

        if (value <= old_value)
        {
            is_increasing = false;
        }

        if (value >= old_value)
        {
            is_decreasing = false;
        }

        if (abs(value - old_value) > 3)
        {
            is_valid = false;
        }

        old_value = value;
    }

    return (is_increasing || is_decreasing) && is_valid;
}

int part1()
{
    auto columns = read_input("../day2_1.txt");
    int total_number_valid = 0;

    for (auto& row : columns)
    {
        if (is_row_valid(row))
        {
            total_number_valid++;
        }
    }

    return total_number_valid;
}

// This is like part1 except that we try calling is_row_valid with the base row and then
// with each of the elements removed in turn. If any of those calls are valid then count the row.
int part2()
{
    auto columns = read_input("../day2_1.txt");
    int total_number_valid = 0;

    for (auto& row : columns)
    {
        if (is_row_valid(row))
        {
            total_number_valid++;
        }
        else
        {
            for (size_t i = 0; i < row.size(); i++)
            {
                std::vector<int> row_copy = row;
                row_copy.erase(row_copy.begin() + i);
                if (is_row_valid(row_copy))
                {
                    total_number_valid++;
                    break;
                }
            }
        }
    }

    return total_number_valid;
}

int main()
{
    std::cout << part1() << std::endl;
    std::cout << part2() << std::endl;
    return 0;
}