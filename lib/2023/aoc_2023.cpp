#include <iomanip>

#include "aoc_2023.h"
#include <file_utils.h>

#include "day01.h"
// #include "day02.h"
// #include "day03.h"
// #include "day04.h"
// #include "day05.h"
// #include "day06.h"
// #include "day07.h"
// #include "day08.h"
// #include "day09.h"
// #include "day10.h"
// #include "day11.h"
// #include "day12.h"
// #include "day13.h"
// #include "day14.h"
// #include "day15.h"
// #include "day16.h"
// #include "day17.h"
// #include "day18.h"
// #include "day19.h"
// #include "day20.h"
// #include "day21.h"
// #include "day22.h"
// #include "day23.h"
// #include "day24.h"
// #include "day25.h"

#include <algorithm>

namespace AoC
{
    /// Challenge: Base class
    Challenge::Challenge()
        : _verbose{false}
    {
    }
    
    Challenge::~Challenge()
    {
    }

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

    std::unique_ptr<Challenge> AoC2023::get_challenge(const Day& day) const
    {
        if (day == Day::day01)
        {
            return std::make_unique<Day01>(day);
        }

        return nullptr;
    }

    std::string AoC2023::get_data_file_name(const Day& day, const std::string& prefix) const
    {
        auto number = static_cast<int>(day);
        std::stringstream ss;
        ss << prefix << std::setw(2) << std::setfill('0') << number << ".txt";

        return AoC::get_input_file_path(ss.str());
    }

    void AoC2023::error(const std::string& message) const
    {
        std::cout << message << "\n";
    }

} // namespace AoC