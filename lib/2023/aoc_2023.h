#ifndef AOC_2023_H
#define AOC_2023_H

#include <string>
#include <memory>
#include <sstream>

namespace AoC
{
    enum class ChallengePart
    {
        first,
        second
    };

    enum class Day
    {
        day01 = 1,
        day02,
        day03,
        day04,
        day05,
        day06,
        day07,
        day08,
        day09,
        day10,
        day11,
        day12,
        day13,
        day14,
        day15,
        day16,
        day17,
        day18,
        day19,
        day20,
        day21,
        day22,
        day23,
        day24,
        day25,
    };

    class Challenge
    {
    public:
        Challenge();
        ~Challenge();

        virtual std::string get_answer(const ChallengePart& part) const = 0;
        inline bool& verbose() { return _verbose; }

    private:
        bool _verbose;
    };

    class AoC2023
    {
    public:
        static AoC2023& get_instance();
        AoC2023(AoC2023 const&) = delete;
        void operator=(AoC2023 const&) = delete;

        std::unique_ptr<Challenge> get_challenge(const Day& day) const;
        std::string get_data_file_name(const Day& day, const std::string& prefix = "input") const;

        template<typename _Type>
        std::string format_answer(const _Type& value) const
        {
            std::stringstream formatter;
            formatter << value;
            return formatter.str();
        }

        void error(const std::string& message) const;

    private:
        AoC2023();
        ~AoC2023();
    };
}

#endif // AOC_2023_H