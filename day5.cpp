#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

struct DependencyItem
{
    int before;
    int after;
};

void part1()
{
    std::vector<DependencyItem> dependencies;

    std::ifstream input_file("../day5.txt");
    std::string line;
    while (std::getline(input_file, line) && !line.empty())
    {
        DependencyItem item;
        item.before = std::stoi(line.substr(0, line.find('|')));
        item.after = std::stoi(line.substr(line.find('|') + 1));
        dependencies.push_back(item);
    }

    std::vector<std::vector<int>> updates;
    while (std::getline(input_file, line))
    {
        std::vector<int> update;
        size_t pos = 0;
        while ((pos = line.find(',')) != std::string::npos)
        {
            update.push_back(std::stoi(line.substr(0, pos)));
            line.erase(0, pos + 1);
        }
        update.push_back(std::stoi(line));
        updates.push_back(update);
    }

    // Check each of the updates in turn
    int total = 0;
    for(auto &update : updates)
    {
        bool is_valid = true;
        // For each update, check if each dependency is satisfied
        for(auto &item : dependencies)
        {
            // Find the position of the before and after numbers in the update list
            auto before = std::find(update.begin(), update.end(), item.before);
            auto after = std::find(update.begin(), update.end(), item.after);
            // If both the before and after numbers are found in the update, check the order

            bool before_found = before != update.end();
            bool after_found = after != update.end();
            bool before_after_order = before > after;

            if (before_found && after_found && before_after_order)
            {
                is_valid = false;
                break;
            }

        }
        if (is_valid)
        {
            int middle_number_of_update = update.size() / 2;
            total += update[middle_number_of_update];
                
        }
    
    }
    std::cout << total << std::endl;
}

void print_vec(std::vector<int> &vec)
{
    for(auto &item : vec)
    {
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

void part2()
{
    std::vector<DependencyItem> dependencies;

    std::ifstream input_file("../day5.txt");
    std::string line;
    while (std::getline(input_file, line) && !line.empty())
    {
        DependencyItem item;
        item.before = std::stoi(line.substr(0, line.find('|')));
        item.after = std::stoi(line.substr(line.find('|') + 1));
        dependencies.push_back(item);
    }

    std::vector<std::vector<int>> updates;
    while (std::getline(input_file, line))
    {
        std::vector<int> update;
        size_t pos = 0;
        while ((pos = line.find(',')) != std::string::npos)
        {
            update.push_back(std::stoi(line.substr(0, pos)));
            line.erase(0, pos + 1);
        }
        update.push_back(std::stoi(line));
        updates.push_back(update);
    }

    // Check each of the updates in turn
    int total = 0;
    for(auto &update : updates)
    {
        bool is_valid = true;
        // For each update, check if each dependency is satisfied
        for(auto &item : dependencies)
        {
            // Find the position of the before and after numbers in the update list
            auto before = std::find(update.begin(), update.end(), item.before);
            auto after = std::find(update.begin(), update.end(), item.after);
            // If both the before and after numbers are found in the update, check the order

            bool before_found = before != update.end();
            bool after_found = after != update.end();
            bool before_after_order = before > after;

            if (before_found && after_found && before_after_order)
            {
                is_valid = false;
                break;
            }

        }

        if (!is_valid)
        {
            print_vec(update);
            // For each dependency, check if the before number is in the update and if not swap them
            std::sort(update.begin(), update.end(), [&dependencies](int a, int b) {
                for (const auto& item : dependencies) {
                    if (item.before == a && item.after == b) {
                        return true;
                    }
                }
                return false;
            });
            print_vec(update);
        int middle_number_of_update = update.size() / 2;
        total += update[middle_number_of_update];
        }
        std::cout << "\n";

    
    }
    std::cout << total << std::endl;
}


int main()
{
    part1();
    part2();
}