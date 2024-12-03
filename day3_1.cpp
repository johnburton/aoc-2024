#include <fstream>
#include <iostream>
#include <regex>

std::string read_entire_file(const std::string& file_name)
{
    std::ifstream input_file{file_name};
    std::string text = std::string{std::istreambuf_iterator<char>(input_file), std::istreambuf_iterator<char>()};
    return text;
}

int test1()
{
    auto input_text = read_entire_file("../day3_1.txt");

    // Create a regex which matches "mul(X,Y)" exactly where X and Y are integers that need to be extracted.
    // It can also match the pattern do() and the pattern dont() with no parameters
    auto regex = std::regex{"mul\\((\\d+),(\\d+)\\)"};

    // Find all of the matches in the input text.
    auto matches_begin = std::sregex_iterator(input_text.begin(), input_text.end(), regex);

    // Iterate over the matches and print out the two integers that were extracted.
    int result = 0;
    for (auto it = matches_begin; it != std::sregex_iterator{}; it++)
    {
        auto match = *it;
        auto x = std::stoi(match[1]);
        auto y = std::stoi(match[2]);
        result += x * y;
    }
    return result;
}

int test2()
{
    auto input_text = read_entire_file("../day3_1.txt");

    // Create a regex which matches "mul(X,Y)" exactly where X and Y are integers that need to be extracted.
    // It can also match the pattern do() and the pattern dont() with no parameters
    auto regex = std::regex{"(mul\\((\\d+),(\\d+)\\))|(do\\(\\))|(don't\\(\\))"};

    // Find all of the matches in the input text.
    auto matches_begin = std::sregex_iterator(input_text.begin(), input_text.end(), regex);

    // Iterate over the matches and print out the two integers that were extracted.
    int result = 0;
    bool is_enabled = true;
    for (auto it = matches_begin; it != std::sregex_iterator{}; it++)
    {
        if (it->str() == "do()")
        {
            is_enabled = true;
        }
        else if (it->str() == "don't()")
        {
            is_enabled = false;
        }
        else if (is_enabled)
        {
            auto match = *it;
            auto x = std::stoi(match[2]);
            auto y = std::stoi(match[3]);
            result += x * y;
        }
    }
    return result;
}

int main()
{
    std::cout << test1() << std::endl;
    std::cout << test2() << std::endl;
}