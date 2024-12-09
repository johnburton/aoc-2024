#include <fstream>
#include <vector>
#include <iostream>

struct File_Entry
{
    int start_position;
    int size;
};

struct Input_Data
{
    std::vector<File_Entry> file_list;
    std::vector<File_Entry> free_list;
};

auto get_input_line() -> std::string
{
    auto input_file = std::ifstream("../day9.txt");
    auto input_line = std::string();
    std::getline(input_file, input_line);
    return input_line;
}

auto expand(std::string_view input_line) -> std::vector<int>
{
    auto input_data       = std::vector<int>();
    auto input_data_index = 0;
    auto file_id          = 0;
    auto is_data          = true;

    while (input_data_index < input_line.size())
    {
        if (is_data)
        {
            auto size_of_file = input_line[input_data_index] - '0';
            auto file_data = std::vector<int>(size_of_file, file_id);
            input_data.insert(input_data.end(), file_data.begin(), file_data.end());

            input_data_index += 1;
            file_id += 1;
        }
        else
        {
            auto size_of_free = input_line[input_data_index] - '0';
            auto free_data = std::vector<int>(size_of_free, -1);
            input_data.insert(input_data.end(), free_data.begin(), free_data.end());

            input_data_index += 1;
        }
        is_data = !is_data;
    }
    return input_data;
}

#include <algorithm>

auto get_max_file_id(std::vector<int>& input_data) -> int
{
    return *std::max_element(input_data.begin(), input_data.end());
}

auto compress_2(std::vector<int>& input_data)
{
    auto max_file_id = get_max_file_id(input_data);

    for (int file_id = max_file_id; file_id >= 0; file_id -= 1)
    {
        auto file_start = std::find(input_data.begin(), input_data.end(), file_id);
        auto file_end   = std::find(file_start, input_data.end(), file_id + 1);

        auto file_size = std::distance(file_start, file_end);

        for (int i = 0; i < file_size; i += 1)
        {
            auto free_start = std::find(input_data.begin(), input_data.end(), -1);
            auto free_end   = std::find(free_start, input_data.end(), 0);

            auto free_size = std::distance(free_start, free_end);

            if (free_size >= file_size)
            {
                std::fill(file_start, file_end, -1);
                std::fill(free_start, free_start + file_size, file_id);
                break;
            }
        }
    }

}


auto compress_1(std::vector<int>& input_data)
{
    auto max_file_id = get_max_file_id(input_data);

    for (int file_id = max_file_id; file_id >= 0; file_id -= 1)
    {
        auto file_start = std::find(input_data.begin(), input_data.end(), file_id);
        auto file_end   = std::find_if(file_start, input_data.end(), [file_id](int x) { return x != file_id; });

        auto file_size = std::distance(file_start, file_end);

        for (int i = 0; i < file_size; i += 1)
        {
            auto free_start = std::find(input_data.begin(), input_data.end(), -1);
            if (free_start > file_start)
            {
                return;
            }
            *free_start = file_id;
            *file_start = -1;
            file_start++;
        }
    }
}

auto part2() -> void
{
    auto input_line = get_input_line();
    auto input_data = expand(input_line);
    compress_2(input_data);
}

unsigned long long checksum(std::vector<int>& input_data)
{
    auto checksum = 0ull;

    for (int i = 0; i < input_data.size(); i += 1)
    {
        if (input_data[i] != -1)
        {
            checksum += (i * input_data[i]);
        }
    }

    return checksum;
}

auto part1() -> void
{
    auto input_line = get_input_line();
    auto input_data = expand(input_line);
    compress_1(input_data);

    // Print input_data
    for (int i = 0; i < input_data.size(); i += 1)
    {
        if (input_data[i] == -1)
        {
            std::cout << ".";
        }
        else
        {
            std::cout << input_data[i];
        }
    
    }
    std::cout << "\n";

    std::cout << "Checksum for part 1 is " << checksum(input_data) << "\n";
}


int main()
{
    part1();
}