#ifndef DAY01_H
#define DAY01_H

#include "aoc_2023.h"

namespace AoC
{
    class Day01 : public Challenge
    {
    public:
        Day01();
        ~Day01();

        std::string get_answer(const ChallengePart& part) const override;

    private:
        static const char *words[];
        static const char *sdrow[];
        static const char *numbers[];

        int find_digit(const std::string& line, bool includeWords, bool reverse);
    }
}

#endif // DAY01_H