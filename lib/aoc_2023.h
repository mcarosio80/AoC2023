#ifndef AOC_2023_H
#define AOC_2023_H

#include <string>
#include <memory>

namespace Aoc
{
    // enum class ChallengePart
    // {
    //     first,
    //     second
    // };

    // class Challenge
    // {
    // public:
    //     Challenge();
    //     ~Challenge();

    //     virtual std::string get_answer(const ChallengePart& part) const = 0;
    // };

    // class Day01 : public Challenge
    // {
    // public:
    //     Day01();
    //     ~Day01();

    //     std::string get_answer(const ChallengePart& part) const;

    // private:
    //     static const char *words[];
    //     static const char *sdrow[];
    //     static const char *numbers[];
    // };

    // class Day02 : public Challenge
    // {
    // public:
    //     Day02();
    //     ~Day02();

    //     std::string get_answer(const ChallengePart& part) const;
    // };

    class AoC2023
    {
    public:
        static AoC2023& get_instance();
        AoC2023(AoC2023 const&) = delete;
        void operator=(AoC2023 const&) = delete;

        template<class _ChallengeDay>
        std::unique_ptr<_ChallengeDay> get_challenge() const
        {
            return std::make_unique<_ChallengeDay>();
        }

    private:
        AoC2023();
        ~AoC2023();
    };
}

#endif // AOC_2023_H