#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <map>

int get_num_digits(uint64_t num)
{
    int count = 0;
    while (num != 0)
    {
        num /= 10;
        count++;
    }
    return count;
}

uint64_t first_half(uint64_t n)
{
    std::string s = std::to_string(n);
    return std::stoull(s.substr(0, s.size() / 2));
}

uint64_t second_half(uint64_t n)
{
    std::string s = std::to_string(n);
    return std::stoull(s.substr(s.size() / 2));
}

std::map<uint64_t, std::map<uint64_t, uint64_t>> memo;

uint64_t count(const uint64_t n, const int iter)
{
    if (iter == 0)
    {
        memo[n][iter] = 1;
        return 1;
    }
    // If we have seen this request before just return the answer
    if (memo.find(n) != memo.end() && memo[n].find(iter) != memo[n].end())
    {
        return memo[n][iter];
    }

    if (n == 0)
    {
        auto result = count(1, iter - 1);
        memo[n][iter] = result;
        return result;
    }
    else if (get_num_digits(n) % 2 == 0)
    {
        auto result = count(first_half(n), iter - 1) + count(second_half(n), iter - 1);
        memo[n][iter] = result;
        return result;
    } 
    else {
        auto result = count(n * 2024, iter - 1);
        memo[n][iter] = result;
        return result;
    }
}

uint64_t count_all(std::vector<uint64_t> stones, int num_iterations)
{
    uint64_t c = 0;
    for (int i = 0; i < stones.size(); i++)
    {
        c += count(stones[i], num_iterations);
    }
    return c;
}


int main()
{
    std::cout << "Test: " << count_all({125, 17}, 25) << "\n";
    std::cout << "Real: " << count_all({1950139,0,3,837,6116,18472,228700,45}, 75) << "\n";
}   