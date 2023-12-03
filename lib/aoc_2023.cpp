#include "aoc_2023.h"
#include <file_utils.h>

#include <algorithm>

namespace AoC
{
    // /// Challenge: Base class
    // Challenge::Challenge()
    // {
    // }
    
    // Challenge::~Challenge()
    // {
    // }

    // /// DAY 01 ------------------------------------------------

    // const char *Day01::words[] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    // const char *Day01::sdrow[] = { "orez", "eno", "owt", "eerht", "ruof", "evif", "xis", "neves", "thgie", "enin"};
    // const char *Day01::numbers[] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    
    // Day01::Day01()
    //     : Challenge() 
    // {
    // }
    
    // Day01::~Day01()
    // {
    // }

    // std::string Day01::get_answer(const ChallengePart& part) const
    // {
    // }

    // /// DAY 02 ------------------------------------------------
    // Day02::Day02()
    //     : Challenge()
    // {
    // }
    
    // Day02::~Day02()
    // {
    // }

    // std::string Day02::get_answer(const ChallengePart& part) const
    // {
    // }

    /// Factory class ------------------------------------------------
    AoC2023& AoC2023::get_instance()
    {
        static AoC2023 _instance;
        return _instance;
    }

    AoC2023::AoC2023()
    {
    }

    AoC2023::~AoC2023()
    {
    }
} // namespace AoC