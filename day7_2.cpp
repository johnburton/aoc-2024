#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <iostream>

struct Problem_Line {
    int64_t expected;
    std::vector<int64_t> numbers;
};

// A line consists of a number, followed by a colon, followed by a list of numbers separated by spaces
Problem_Line parse_line(std::istream& is) {
    Problem_Line line;

    is >> line.expected;
    int64_t number;
    char sep; is >> sep;
    while (is >> number) {
        line.numbers.push_back(number);
    }
    return line;
}

std::vector<Problem_Line> parse_input(std::istream& is) {
    std::vector<Problem_Line> lines;
    std::string line;
    while (std::getline(is, line)) {
        std::istringstream iss(line);
        lines.push_back(parse_line(iss));
    }
    return lines;
}

enum Operation {
    Add = 0,
    Multiply = 1,
    Concatenate = 2
};

bool is_correct(Problem_Line problem, std::vector<Operation> operations)
{
    auto result = problem.numbers[0];
    for (int i = 0; i < problem.numbers.size() - 1; i++)
    {
        if (operations[i] == Operation::Add)
        {
            result += problem.numbers[i + 1];
        }
        else if (operations[i] == Operation::Multiply)
        {
            result *= problem.numbers[i + 1];
        }
        else if (operations[i] == Operation::Concatenate)
        {
            auto result_as_string = std::to_string(result);
            auto next_number_as_string = std::to_string(problem.numbers[i + 1]);
            result = std::stoll(result_as_string + next_number_as_string);
        }
    }

    return result == problem.expected;
}

// Generate the next combination of operations
// Return false if this is final combination

bool next_combination(std::vector<Operation>& operations)
{
    for (int i = operations.size() - 1; i >= 0; i--)
    {
        if (operations[i] == Operation::Add)
        {
            operations[i] = Operation::Multiply;
            return true;
        }
        else if (operations[i] == Operation::Multiply)
        {
            operations[i] = Operation::Concatenate;
            return true;
        }
        else
        {
            operations[i] = Operation::Add;
        }
    }
    return false;
}

void print(std::vector<Operation> operations)
{
    for (auto op: operations)
    {
        if (op == Operation::Add)
        {
            std::cout << "+";
        }
        else
        {
            std::cout << "*";
        }
    }
    std::cout << std::endl;
}


bool check_problem(Problem_Line problem)
{
    auto number_of_operators = problem.numbers.size() - 1;
    std::vector<Operation> operations { number_of_operators, Operation::Add };

    if (is_correct(problem, operations))
    {
        return true;
    }

    while(next_combination(operations))
    {
        if (is_correct(problem, operations))
        {
            return true;
        }
    }
    return false;
}

int main()
{
    std::ifstream input_file("../day7.txt");
    auto lines = parse_input(input_file);

    int64_t result = 0;

    for (auto problem: lines)
    {
        auto valid = check_problem(problem);
        if (valid)
        {
            result += problem.expected;
        }
    }
    std::cout << result << std::endl;
}