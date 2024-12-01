#include <algorithm>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

auto read_input(const std::string& file_name)
{
    std::ifstream input_file{file_name};

    std::vector<int> column_1;           
    std::vector<int> column_2;

    int value_1, value_2;
    while(input_file >> value_1 >> value_2)
    {
        column_1.push_back(value_1);
        column_2.push_back(value_2);
    }

    return std::make_pair(column_1, column_2);
}


int part1()
{
    auto [column_1, column_2] = read_input("../day1_1.txt");

    std::sort(begin(column_1), end(column_1));
    std::sort(begin(column_2), end(column_2));

    long long total_diff = 0;
    for (size_t i = 0; i < column_1.size(); i++) {
        total_diff += std::abs(column_1[i] - column_2[i]);
    }

    return total_diff;
}

int part2()
{
    auto [column_1, column_2] = read_input("../day1_1.txt");

    std::unordered_map<int, int> column_2_number_counts;

    for (int value: column_2)
    {
        column_2_number_counts[value]++;
    }

    long long total = 0;
    for (size_t i = 0; i < column_1.size(); i++)
    {
        total += column_1[i] * column_2_number_counts[column_1[i]];
    }

    return total;
}

int main()
{
    std::cout << part1() << std::endl;
    std::cout << part2() << std::endl;
}
